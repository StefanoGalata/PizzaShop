// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PizzaShopCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewItemHeld, AActor*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewScoreSet, float, NewScore);

class UInteractionSphereComponent;

UCLASS(config=Game)
class APizzaShopCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APizzaShopCharacter();

	UFUNCTION(BlueprintCallable)
	void SetHoldingItem(AActor* NewHoldingItem);

	UFUNCTION(BlueprintCallable)
	void RemoveHoldingItem();

	UFUNCTION(BlueprintCallable)
	void AddScore(float Score);

	UFUNCTION(BlueprintPure)
	FORCEINLINE AActor* GetHoldingItem() { return HoldingItem; }

	UPROPERTY(BlueprintAssignable)
	FOnNewItemHeld OnNewItemHeld;

	UPROPERTY(BlueprintAssignable)
	FOnNewScoreSet OnNewScoreSet;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	void Interact();
	void StopInteraction();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, Category = "Interactions", meta = (AllowPrivateAccess = true))
	UInteractionSphereComponent* InteractionSphere;

	UPROPERTY()
	AActor* HoldingItem;
};

