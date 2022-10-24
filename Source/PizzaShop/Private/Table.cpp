// Fill out your copyright notice in the Description page of Project Settings.


#include "Table.h"
#include "Components/InteractableComponent.h"
#include <../PizzaShopCharacter.h>
#include "Toppings/ToppingActor.h"
#include <Pizza.h>

// Sets default values
ATable::ATable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Custom Root"));
	CustomRootComponent->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CustomRootComponent);

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable Component"));
	InteractableComponent->SetupAttachment(CustomRootComponent);

	ItemRestLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Item Spawn Location"));
	ItemRestLocation->SetupAttachment(CustomRootComponent);

	RestingItem = nullptr;

}

void ATable::InteractionStarted(ACharacter* InteractingCharacter)
{
	APizzaShopCharacter* PizzaShopCharacter = Cast<APizzaShopCharacter>(InteractingCharacter);
	if (!PizzaShopCharacter)
	{
		return;
	}

	if (RestingItem)
	{
		if (!PizzaShopCharacter->GetHoldingItem())
		{
			PizzaShopCharacter->SetHoldingItem(RestingItem);
			RemoveRestingItem();
		}
		else
		{
			AToppingActor* ToppingActor = Cast<AToppingActor>(PizzaShopCharacter->GetHoldingItem());
			if (!ToppingActor)
			{
				return;
			}

			APizza* RestingPizza = Cast<APizza>(RestingItem);
			if (!RestingPizza)
			{
				return;
			}
			if (!RestingPizza->IsCooked() && !RestingPizza->IsBoxed())
			{
				RestingPizza->AddTopping(ToppingActor->Topping);
				PizzaShopCharacter->RemoveHoldingItem();
				ToppingActor->Destroy();
			}

		}
	}

	else if(PizzaShopCharacter->GetHoldingItem())
	{
		// Rest the player's holding item into the table
		SetRestingItem(PizzaShopCharacter->GetHoldingItem());
		PizzaShopCharacter->RemoveHoldingItem();
		RestingItem->SetActorLocation(ItemRestLocation->GetComponentLocation());
		RestingItem->SetActorRotation(ItemRestLocation->GetComponentRotation());
	}

}

void ATable::InteractionEnded(ACharacter* InteractingCharacter)
{
	
}

void ATable::SetRestingItem(AActor* NewRestingItem)
{
	RestingItem = NewRestingItem;
}

void ATable::RemoveRestingItem()
{
	RestingItem = nullptr;
}

void ATable::BeginPlay()
{
	Super::BeginPlay();

	InteractableComponent->OnInteractionStart.AddDynamic(this, &ATable::InteractionStarted);
	InteractableComponent->OnInteractionEnd.AddDynamic(this, &ATable::InteractionEnded);
}

