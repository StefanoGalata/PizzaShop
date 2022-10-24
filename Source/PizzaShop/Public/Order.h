// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Toppings/Topping.h"
#include "Order.generated.h"

UCLASS()
class PIZZASHOP_API UOrder : public UObject
{
	GENERATED_BODY()

public:
	
	UOrder();

	UFUNCTION(BlueprintPure, Category = "Order")
	FORCEINLINE TArray<TSubclassOf<UTopping>>& GetOrderToppings() { return Toppings; }

	TArray<TSubclassOf<UTopping>> Toppings;
	
	
};
