// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Cell.h"
#include "Components/ActorComponent.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#include "UObject/ConstructorHelpers.h"

#include "Materials/Material.h"

#include "ProceduralMeshComponent.h"
#include "Filament.h"

#include "CellMesh.generated.h"
class UCell;

/** Structure that defines a level up table entry */

UCLASS(BlueprintType)
class CSVIMPORT_API ACellMeshActorComponent : public AActor
{
	GENERATED_BODY()
public:
	ACellMeshActorComponent();

	UPROPERTY()
	USphereComponent* Sphere;
	
	/*stores all created cylinders that make up the stored cytoskeleton*/
	UPROPERTY(BlueprintReadOnly)
	TMap<UPrimitiveComponent*, UFilament*> ComponentCellMap;

	/*Returns a pointer to the currently stored cytoskeleton object*/
	UFUNCTION(BlueprintGetter, Category="Cell")
	UCell* GetCell();
	
	UPROPERTY(BlueprintReadWrite)
	UCell* Cell;

	//Factor needed to normalize the density value
	static float DensityRange;
	static float DensityMin;
	static float DensityScale;
	static float DensityShift;
protected:
	virtual void Tick(float DeltaSeconds) override;
private:
	/*creates a cylinder between Start and End, that represents a vertex and can be rendered to the screen. The result will be stored in ComponentCellMap*/
	void CreateCylinder(
		TArray<FVector>& Vertices, 
		TArray<int32>& Triangles,
		FVector Start, 
		FVector End, 
		float Radius, 
		int Resolution = 12);


};