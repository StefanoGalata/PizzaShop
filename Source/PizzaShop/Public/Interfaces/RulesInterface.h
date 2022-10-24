// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../Order.h"
#include "RulesInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URulesInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PIZZASHOP_API IRulesInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddOrder(UOrder* Order);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool HasOngoingOrder();
};
