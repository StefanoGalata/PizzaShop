// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PizzaShopPlayerController.generated.h"

class UOrder;
class UMainHUD;

UCLASS()
class PIZZASHOP_API APizzaShopPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintPure, Category = "PizzaShopPlayerController|HUD")
	FORCEINLINE UMainHUD* GetMainHud(){return MainHud;}

	UFUNCTION()
	void OrderAdded(UOrder* NewOrder);

	UFUNCTION()
	void OrderRemoved(UOrder* RemovedOrder);

	UFUNCTION()
	void SetNewTime(float NewTime);

	UFUNCTION()
	void SetScoreInHud(float NewScore);

	UFUNCTION()
	void OnPossessedPawnNewItemHeld(AActor* NewItem);

	virtual void OnPossess(APawn* InPawn) override;

protected:

	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UMainHUD> MainHudClass;

	UPROPERTY()
	UMainHUD* MainHud;
};
