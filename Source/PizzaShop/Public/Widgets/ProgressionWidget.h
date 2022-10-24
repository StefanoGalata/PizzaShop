// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProgressionWidget.generated.h"

class UProgressBar;

UCLASS()
class PIZZASHOP_API UProgressionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* ProgressBar;

	UFUNCTION(BlueprintCallable, Category = "Progression Widget")
	void SetWidgetProgression(float Value);
	
};
