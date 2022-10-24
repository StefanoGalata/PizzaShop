// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemModifier.h"
#include "PizzaBoxer.generated.h"

UCLASS()
class PIZZASHOP_API APizzaBoxer : public AItemModifier
{
	GENERATED_BODY()

public:
	virtual void ModifyItem() override;
	virtual bool CanModifyItem(AActor* Item) override;

};
