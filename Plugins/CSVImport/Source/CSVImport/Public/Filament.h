// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CellData.h"

#include "Filament.generated.h"

/** Filaments consist of one or more vertices (vertices are implemented as the class UCellData) */
UCLASS(BlueprintType)
class CSVIMPORT_API UFilament : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	void AddCellData(UCellData* cellData);

	const TArray<UCellData*>& GetVertices() const;

	int32 GetLineNumber() const;

	int32 GetCellClass() const;

	void SetCellClass(int32 Value);

	FBox GetBoundingBox() const;

//private:
	UPROPERTY(BlueprintReadOnly)
	TArray<UCellData*> Vertices;
	UPROPERTY(BlueprintReadOnly)
	int32 LineNumber;
	
	FBox BoundingBox;
};