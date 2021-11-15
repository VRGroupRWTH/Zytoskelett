// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CSVImport/Public/CellMesh.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZytoskelettReader.generated.h"

UCLASS()
class ZYTOSKELETT2_API AZytoskelettReader : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZytoskelettReader();

	// The name (not the path) of the file to load (including file extension)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Eingabe)
	FString filename;

	// The name of the actor to be created
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Eingabe)
	FName skelettDataActorName;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*Reads a file with the name stored in filename by calling the FactoryCreateFile method from UCellDataFactory. Returns the created cytoskeleton mesh.*/
	UFUNCTION(BlueprintCallable)
	ACellMeshActorComponent* ReadZytoskelettFromFile();

};
