// Fill out your copyright notice in the Description page of Project Settings.


#include "CellData.h"

UCellData::UCellData(const FObjectInitializer& objectInitializer)
	:Super(objectInitializer)
{

}

UCellData::UCellData(TArray<FString>& values)
	:Super()
{

}

bool UCellData::FromString(const FString& value)
{
	TArray<FString> values;
	if (value.ParseIntoArray(values, TEXT("\t")) == 8) {
		LineNumber = FCString::Atoi(*values[0]);
		VertexNumber = FCString::Atoi(*values[1]);
		X = FCString::Atof(*values[2]);
		Y = FCString::Atof(*values[3]);
		Z = FCString::Atof(*values[4]);
		Density = FCString::Atof(*values[5]);
		Class = FCString::Atoi(*values[6]);
		Flag = *values[7];
		return true;
	}
	else {
		return false;
	}
}

FString UCellData::ToString() {
	// The resulting string contains all values of CellData separated by a tabulator
	return FString::Printf(TEXT("%i\t%i\t%f\t%f\t%f\t%f\t%i\t%s"), LineNumber, VertexNumber, X, Y, Z, Density, Class, *Flag);
}
