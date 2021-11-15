// Fill out your copyright notice in the Description page of Project Settings.


#include "Cell.h"
#include "Engine/World.h"

#include "UObject/ConstructorHelpers.h"
#include "UObject/UObjectGlobals.h"

UCell::UCell(UFilament* filament)
	:Super()
{}

UCell::UCell(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer) 
{

}
	
void UCell::AddCellData(UCellData* cellData)
{
	UFilament* found = nullptr;
	for (UFilament* filament : Filaments)
	{
		if (cellData->LineNumber == filament->GetLineNumber()) {
			found = filament;
			break;
		}
	}

	if (found != nullptr)
	{
		found->AddCellData(cellData);
		Boundingbox += found->GetBoundingBox();
	}
	else {
		UFilament* filament = NewObject<UFilament>(this);
		filament->AddCellData(cellData);
		Filaments.Add(filament);
		Boundingbox += filament->GetBoundingBox();
	}
}

void UCell::AddFilament(UFilament* filament)
{
	auto Predicate = [filament](UFilament* current) {
		return filament->GetLineNumber() == current->GetLineNumber();
	};
	UFilament* found = *Filaments.FindByPredicate(Predicate);

	if (found == nullptr) {
		Filaments.Add(filament);
		Boundingbox += filament->GetBoundingBox();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Filament with LineNumber %i is already a part of this cell."), filament->GetLineNumber());
	}
}

const TArray<UFilament*>& UCell::GetFilaments() const {
	return Filaments;
}

FBox UCell::GetBoundingBox() const {
	return Boundingbox;
}
