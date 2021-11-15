// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"

#include "Cell.h"
#include "CellMesh.h"


#include "Engine/World.h"

#include "CellDataFactory.generated.h"

/**
 * 
 */

UCLASS(hidecategories = Object)
class CSVIMPORT_API UCellDataFactory : public UFactory
{
	GENERATED_UCLASS_BODY()
public:
	/*
	* \brief Reads a file and creates UCellData Objects from it. The file needs to have the correct format, otherwise none are created. Overriden from the UFactory class. Also Creates an actor in the subfolder /Content/Data
	*
	* \params InClass Not needed, set it to NULL
	* \params InParent Should be set to NULL
	* \params InName The name of the created actor
	* \params Flags Set it to EObjectFlags::RF_NoFlags
	* \params Filename The filepath and filename of the file to read data from
	* \params Parms Should be NULL
	* \params Warn Should be NULL
	* \params bOutputOperationCanceled A bool variable that indicates whether the fileread was cancelled.
	*/
	virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;

	/*returns a pointer to the stored cytoskeleton object*/
	static UCell* GetCell();

	/*stores a pointer to the generated mesh*/
	UPROPERTY(BlueprintReadOnly)
		ACellMeshActorComponent* GeneratedActor;

private:
	/*a pointer to the last generated cytoskeleton*/
	static UCell* Cell;

};