// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CellData.h"
#include "Filament.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Cell.generated.h"


UCLASS()
class CSVIMPORT_API UCell : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	UCell(UFilament* filament);

	void AddCellData(UCellData* cellData);
	void AddFilament(UFilament* filament);

	const TArray<UFilament*>& GetFilaments() const;

	UFUNCTION(BlueprintCallable)
	FBox GetBoundingBox() const;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Collision")
	FBox Boundingbox;
	
private:
	UPROPERTY() TArray<UFilament*> Filaments;
	
};