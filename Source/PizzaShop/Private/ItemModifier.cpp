// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemModifier.h"
#include "Components/WidgetComponent.h"
#include <../PizzaShopCharacter.h>
#include "Components/AudioComponent.h"

void AItemModifier::GenerateItem()
{
	ModifyItem();
	NewItem = ItemBeingModified;
	NewItem->SetActorLocation(ItemSpawnLocation->GetComponentLocation());
	NewItem->SetActorRotation(ItemSpawnLocation->GetComponentRotation());
	ProgressionWidget->SetVisibility(false);
	ItemBeingModified = nullptr;
}

void AItemModifier::ModifyItem()
{
	if (ItemStartGenerationSoundComponent)
	{
		ItemStartGenerationSoundComponent->Stop();
		ItemStartGenerationSoundComponent->DestroyComponent();
		ItemStartGenerationSoundComponent = nullptr;
	}
}

void AItemModifier::InteractionStarted(ACharacter* InteractingCharacter)
{
	APizzaShopCharacter* PizzaShopCharacter = Cast<APizzaShopCharacter>(InteractingCharacter);
	if (PizzaShopCharacter)
	{
		if (PizzaShopCharacter->GetHoldingItem() != nullptr)
		{
			if (CanModifyItem(PizzaShopCharacter->GetHoldingItem()))
			{
				ItemBeingModified = PizzaShopCharacter->GetHoldingItem();
				PizzaShopCharacter->RemoveHoldingItem();

				StartItemGeneration();
			}
		}
		else if (NewItem)
		{
			PizzaShopCharacter->SetHoldingItem(NewItem);
			NewItem = nullptr;
		}
	}
}

bool AItemModifier::CanModifyItem(AActor* Item)
{
	
	return false;
}

void AItemModifier::InteractionEnded(ACharacter* InteractingCharacter)
{

}
