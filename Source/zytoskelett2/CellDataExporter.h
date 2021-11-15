// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CellMesh.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CellDataExporter.generated.h"


UCLASS()
class ZYTOSKELETT2_API ACellDataExporter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACellDataExporter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* takes the cytoskeletons mesh and a filename. Extracts the pointer to the corresponding cytoskeleton object and writes the
	*  filaments' data into a file with the given name. The file will be stored in the /Content/Data subdirectory.
	*/
	UFUNCTION(BluePrintCallable)
	bool ExportCellData(ACellMeshActorComponent* cellMesh , FString fileName);
	//bool ExportCellData(UCell* cell, FString fileName);

};
