// Fill out your copyright notice in the Description page of Project Settings.

#include "CellDataFactory.h"

#include "Misc/FileHelper.h"
#include "Engine/Engine.h"

#include "Engine/StaticMesh.h"

#include "CellData.h"

#include "UObject/UObjectGlobals.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#include "UObject/ConstructorHelpers.h"

#include "Editor/GroupActor.h"

#include "Engine/StaticMeshActor.h"

#include "Misc/FileHelper.h"

#include <string>

UCell* UCellDataFactory::Cell = nullptr;

UCellDataFactory::UCellDataFactory(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	Formats.Add(FString("dat;") + NSLOCTEXT("UCellDataFactory", "FormatCSV", "CSVFile").ToString());
	SupportedClass = AStaticMeshActor::StaticClass();
	bCreateNew = false;
	bEditorImport = true;

	
}

UObject* UCellDataFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	TArray<FString> FileAsLines;
	FFileHelper::LoadFileToStringArray(FileAsLines, *Filename);
	TArray<FString> lines;
	FileAsLines.RemoveAt(0);

	float MinDensity =  100000000.f;
	float MaxDensity = -100000000.f;
	
	UCell* cell = NewObject<UCell>();
	for (FString line : FileAsLines) {
		UCellData* cellData = NewObject<UCellData>();
		cellData->FromString(line);
		cell->AddCellData(cellData);

		MinDensity = FMath::Min(MinDensity, cellData->Density);
		MaxDensity = FMath::Max(MaxDensity, cellData->Density);
	}

	ACellMeshActorComponent::DensityRange = MaxDensity - MinDensity;
	ACellMeshActorComponent::DensityMin = MinDensity;
	
	UCellDataFactory::Cell = cell;

	FString packageName = TEXT("/Game/Data/");
	packageName += InName.ToString();
	const auto Package = CreatePackage(nullptr, *packageName);

	// This has the side effect of creating the meshes, since UCellDataFactory::Cell is now set!
	ACellMeshActorComponent* actor = NewObject<ACellMeshActorComponent>(Package, InName, RF_Public | RF_Standalone | RF_MarkAsRootSet);
	
	return actor;
}

UCell* UCellDataFactory::GetCell() {
	return UCellDataFactory::Cell;
}

