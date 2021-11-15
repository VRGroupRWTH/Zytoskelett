// Fill out your copyright notice in the Description page of Project Settings.


#include "Filament.h"

UFilament::UFilament(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer) {}

void UFilament::AddCellData(UCellData* cellData)
{
	if (Vertices.Num() == 0) {
		Vertices.Add(cellData);
		BoundingBox += FVector(cellData->X, cellData->Y, cellData->Z);
		LineNumber = cellData->LineNumber;
	}
	else{
		if (LineNumber == cellData->LineNumber) {
			Vertices.Add(cellData);
			BoundingBox += FVector(cellData->X, cellData->Y, cellData->Z);
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("cellData has LineNumber %i but filament has LineNumber %i"), cellData->LineNumber, Vertices[0]->LineNumber);
		}
	}
}

const TArray<UCellData*>& UFilament::GetVertices() const
{
	return Vertices;
}

int32 UFilament::GetLineNumber() const
{
	if (Vertices.Num() == 0)
	{
		return -1;
	}
	else
	{
		return Vertices[0]->LineNumber;
	}
}

int32 UFilament::GetCellClass() const {
	return Vertices[0]->Class;
}

void UFilament::SetCellClass(int32 Value) {
	for (UCellData* CellData : Vertices) {
		CellData->Class = Value;
	}
}

FBox UFilament::GetBoundingBox() const {
	return BoundingBox;
}
