// Fill out your copyright notice in the Description page of Project Settings.


#include "DataHolderActor.h"

// Sets default values
ADataHolderActor::ADataHolderActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADataHolderActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADataHolderActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

