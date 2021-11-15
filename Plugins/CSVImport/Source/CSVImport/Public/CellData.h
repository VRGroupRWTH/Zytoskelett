// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CellData.generated.h"

// An element of this class is called vertex 


/** Structure that defines a level up table entry */
UCLASS(Blueprintable)
class CSVIMPORT_API UCellData : public UObject
{
    GENERATED_UCLASS_BODY()

public:
	UCellData(TArray<FString>& values);

	bool FromString(const FString& values);
	FString ToString();

    /** The number of the line to which this vertex belongs */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CellData")
    int32 LineNumber;

	/** The number of the current vertex*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CellData")
    int32 VertexNumber;

	/** The x coordinate*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CellData")
    float X;

	/** The y coordinate*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CellData")
	float Y;

	/** The z coordinate*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CellData")
	float Z;

	/** The density of a filament*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CellData")
	float Density;
	
	/** The Class of a filament*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CellData")
	int32 Class;

	/** A Flag column which will be filled later */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category="CellData")
	FString Flag = "NaN";
private:
	float MinDensity = 999999999.f;
	float MaxDensity = -999999999.f;

	
};
