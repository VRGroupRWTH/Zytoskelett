// Fill out your copyright notice in the Description page of Project Settings. 

#include "CellDataExporter.h"

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

#include "Cell.h"
#include "Filament.h"
#include "CellData.h"
#include "Animation/AnimCurveTypes.h"



// Sets default values
ACellDataExporter::ACellDataExporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACellDataExporter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACellDataExporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACellDataExporter::ExportCellData(ACellMeshActorComponent* cellMesh, FString fileName)
{
	if (!cellMesh)
	{
		return false;
	}

	UCell* cell = cellMesh->GetCell();

	FString filePath = FPaths::ProjectContentDir() + "Data/";
	filePath.Append(fileName);

	FString fileContent = "n_segment\tn_vert\tx\ty\tz\tdensity\tclass\tflag\n";

	for (UFilament* filament : cell->GetFilaments())
	{
		for (UCellData* vertex : filament->GetVertices())
		{
			fileContent.Append(vertex->ToString() + "\n");
		}
	}

	bool fileWrittenSuccessfully = FFileHelper::SaveStringToFile(fileContent, *filePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_None);

	return fileWrittenSuccessfully;
}

