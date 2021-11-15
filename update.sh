#!/bin/sh

if [ ! -f "update.txt" ]
then
    echo "The file update.txt does not exists."
    echo "Make sure setup.sh has been run and the file is checked in into git."
    exit -1
fi
readarray -n 2 -t update < update.txt
remote=${update[0]}
branch=${update[1]}

template_remote=$(git remote | grep template-origin)
if [ -z "$template_remote" ]
then
    echo "Add remote for the template."
    git remote add template-origin "${update[0]}"
else
    old_remote=$(git remote get-url template-origin)
    if [ $old_remote != $remote ]
    then
        echo "The remote for the template changed, updating it."
        git remote remove template-origin
        git remote add template-origin "${update[0]}"
    fi
fi

# Check if remote exists
if ! git ls-remote "$remote" &> /dev/null
then
    echo "The remote '$remote' is not a valid git repository."
    echo "Please update the first line in 'update.txt'."
    exit -1
fi

# Check if remote branch exists
if ! git ls-remote --exit-code --heads "$remote" "$branch" &> /dev/null
then
    echo "The branch '$branch' does not exist on the remote repository."
    echo "Please update the second line in 'update.txt'."
    exit -2
fi

git fetch template-origin $branch
git merge template-origin/$branch
echo "Done!"
