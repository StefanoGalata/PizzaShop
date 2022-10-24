// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Topping.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PIZZASHOP_API UTopping : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Topping")
	FText ToppingName;
	
};
