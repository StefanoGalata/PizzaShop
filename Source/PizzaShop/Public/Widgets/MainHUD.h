// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUD.generated.h"

class UOrder;
class UVerticalBox;

UCLASS()
class PIZZASHOP_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetOngoingOrder(UOrder* Order);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetPlayerHoldingItemUI(AActor* HoldingActor);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "PizzaShopGameMode")
	void SetTimeUI(int32 Time);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void RemoveOngoingOrder();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetScoreUI(float NewScore);
	
};
