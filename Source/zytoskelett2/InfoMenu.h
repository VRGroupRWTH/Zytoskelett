// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "InfoMenu.generated.h"

/**
 * 
 */
UCLASS(ABSTRACT)
class ZYTOSKELETT2_API UInfoMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* SelectedClass;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* LineNumber;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* VertexNumber;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Class;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* ClassImage;
};
