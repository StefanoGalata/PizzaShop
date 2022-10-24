// Fill out your copyright notice in the Description page of Project Settings.


#include "Oven.h"
#include "Pizza.h"

void AOven::ModifyItem()
{
	Super::ModifyItem();
	APizza* Pizza = Cast<APizza>(ItemBeingModified);
	if (Pizza)
	{
		Pizza->SetIsCooked(true);
	}
}

bool AOven::CanModifyItem(AActor* Item)
{
	APizza* Pizza = Cast<APizza>(Item);
	if (Pizza)
	{
		return (!Pizza->IsCooked() && !Pizza->IsBoxed());
	}
	return false;
}
