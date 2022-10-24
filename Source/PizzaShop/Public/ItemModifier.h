// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBox.h"
#include "ItemModifier.generated.h"

/**
 * 
 */
UCLASS()
class PIZZASHOP_API AItemModifier : public AItemBox
{
	GENERATED_BODY()

public:
	
	AItemModifier() : ItemBeingModified(nullptr) {};

	virtual void GenerateItem() override;

	UFUNCTION(BlueprintCallable, Category ="Item Modifier")
	virtual void ModifyItem();

	UFUNCTION(BlueprintCallable, Category = "Item Modifier")
	virtual bool CanModifyItem(AActor* Item);

	virtual void InteractionStarted(ACharacter* InteractingCharacter) override;

	virtual void InteractionEnded(ACharacter* InteractingCharacter) override;

protected:

	UPROPERTY()
	AActor* ItemBeingModified;
	
};
