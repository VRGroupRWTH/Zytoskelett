// Fill out your copyright notice in the Description page of Project Settings.


#include "ZytoskelettReader.h"
#include "CSVImport/Public/CellDataFactory.h"
#include "CSVImport/Public/CellMesh.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"


// Sets default values
AZytoskelettReader::AZytoskelettReader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void AZytoskelettReader::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AZytoskelettReader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ACellMeshActorComponent* AZytoskelettReader::ReadZytoskelettFromFile()
{
	FString file = FPaths::ProjectContentDir();
	file.Append("Data/" + filename);

	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

	bool output = false;
	UCellDataFactory* CellFactory = NewObject<UCellDataFactory>();
	ACellMeshActorComponent* zytoskelettActor = nullptr;

	if (FileManager.FileExists(*file))
	{
		zytoskelettActor = Cast<ACellMeshActorComponent>(CellFactory->FactoryCreateFile(
			NULL,
			NULL,
			skelettDataActorName,
			EObjectFlags::RF_NoFlags,
			file,
			NULL,
			NULL,
			output));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FileManipulation: ERROR: Can not read the file because it was not found."));
		UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Expected file location: %s"), *file);
	}
	
	return zytoskelettActor;
}
