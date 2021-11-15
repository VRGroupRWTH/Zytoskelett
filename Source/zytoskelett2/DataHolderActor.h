// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataHolderActor.generated.h"

UCLASS()
class ZYTOSKELETT2_API ADataHolderActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADataHolderActor();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Zytoskelett-Eingabe")
	FString filename;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Zytoskelett-Eingabe")
	FName CreatedActorName;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
