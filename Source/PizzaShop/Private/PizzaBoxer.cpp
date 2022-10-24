// Fill out your copyright notice in the Description page of Project Settings.


#include "PizzaBoxer.h"
#include "Pizza.h"

void APizzaBoxer::ModifyItem()
{
	Super::ModifyItem();
	APizza* Pizza = Cast<APizza>(ItemBeingModified);
	if (Pizza)
	{
		Pizza->SetIsBoxed(true);
	}
}

bool APizzaBoxer::CanModifyItem(AActor* Item)
{
	APizza* Pizza = Cast<APizza>(Item);
	if (Pizza)
	{
		return Pizza->IsCooked() && !Pizza->IsBoxed();
	}
	return false;
}

