// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/RulesInterface.h"
#include "PizzaShopGameMode.generated.h"

class UOrder;
class APizza;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOngoingOrderRemoved, UOrder*, Order);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOngoingOrderAdded, UOrder*, Order);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewTimeSet, float, NewTime);

UCLASS(minimalapi)
class APizzaShopGameMode : public AGameModeBase, public IRulesInterface
{
	GENERATED_BODY()

public:
	APizzaShopGameMode();

	virtual void AddOrder_Implementation(UOrder* NewOrder);
	virtual bool HasOngoingOrder_Implementation();

	UFUNCTION(BlueprintCallable, Category = "PizzaShopGameMode")
	bool RemoveMatchingOrder(APizza* Pizza);

	UFUNCTION(BlueprintCallable, Category = "PizzaShopGameMode")
	void StartMatch();

	UFUNCTION(BlueprintImplementableEvent, Category = "PizzaShopGameMode")
	void EndGame();

	UPROPERTY(EditAnywhere, Category = "PizzaShopGameMode")
	float MatchDurationTime;


	void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintAssignable)
	FOnOngoingOrderRemoved OnOngoingOrderRemoved;

	UPROPERTY(BlueprintAssignable)
	FOnOngoingOrderAdded OnOngoingOrderAdded;

	UPROPERTY(BlueprintAssignable)
	FOnNewTimeSet OnNewTimeSet;

private:
	
	bool bMatchStarted;
	
	UPROPERTY()
	UOrder* OngoingOrder;


};



