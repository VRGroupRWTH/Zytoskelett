#!/bin/sh

if [ ! -f "update.txt" ]
then
    remote_branch=$(git rev-parse --abbrev-ref @{u})

    if [[ "$remote_branch" != "origin/"* ]]
    then
        echo "This script can only handle remotes named origin!"
        exit -1
    fi

    remote_branch=${remote_branch#"origin/"}

    repository_url=$(git remote get-url origin)
    echo "$repository_url"

    echo "$repository_url" >> update.txt
    echo "$remote_branch" >> update.txt
fi

current_branch=$(git rev-parse --abbrev-ref HEAD)
branches_to_delete=$(git for-each-ref --format='%(refname:short)' refs/heads/)

for branch in $branches_to_delete
do
    if [ "$branch" != "$current_branch" ]
    then
        git branch -d "$branch"
    fi
done

if [ "$current_branch" != "develop" ]
then
    git checkout -b develop
    git branch -d "$current_branch"
fi

git remote remove origin
git add .
git commit -m "Initial commit"
git branch master

echo "Enter URL of the project's git repository (Leave empty to skip this step):"
read new_remote

if [ -n "$new_remote" ]
then
    echo "Setting up repository..."
    git remote add origin $new_remote
    git push -u origin develop
    git checkout master
    git push -u origin master
fi

echo "Done!"