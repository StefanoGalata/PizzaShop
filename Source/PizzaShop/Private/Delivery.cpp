// Fill out your copyright notice in the Description page of Project Settings.


#include "Delivery.h"
#include <../PizzaShopCharacter.h>
#include <Pizza.h>
#include "Kismet/GameplayStatics.h"
#include "../PizzaShopGameMode.h"
#include "../PizzaShopCharacter.h"
#include "GameFramework/PlayerState.h"
#include <Components/InteractableComponent.h>
#include "Widgets/MainHUD.h"
#include "Kismet/GameplayStatics.h"

ADelivery::ADelivery()
{
	PrimaryActorTick.bCanEverTick = false;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Item Spawn Location"));
	CustomRootComponent->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CustomRootComponent);

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable Component"));
	InteractableComponent->SetupAttachment(CustomRootComponent);

}

bool ADelivery::RemoveMatchingOrder(APizza* Pizza)
{
	APizzaShopGameMode* PizzaShopGameMode = Cast<APizzaShopGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!PizzaShopGameMode)
	{
		return false;
	}
	return PizzaShopGameMode->RemoveMatchingOrder(Pizza);
}

void ADelivery::InteractionStarted(ACharacter* InteractingCharacter)
{
	APizzaShopCharacter* PizzaShopCharacter = Cast<APizzaShopCharacter>(InteractingCharacter);
	if (!PizzaShopCharacter)
	{
		return;
	}
	APizza* PizzaToDelivery = Cast<APizza>(PizzaShopCharacter->GetHoldingItem());
	if (!PizzaToDelivery)
	{
		return;
	}

	if (!PizzaToDelivery->IsCooked() || !PizzaToDelivery->IsBoxed())
	{
		return;
	}
	if (RemoveMatchingOrder(PizzaToDelivery))
	{
		PizzaShopCharacter->RemoveHoldingItem();
		PizzaToDelivery->Destroy();
		PizzaShopCharacter->AddScore(100.f);
		if (DeliverySound)
		{
			UGameplayStatics::PlaySound2D(this, DeliverySound);
		}
	}
}

void ADelivery::BeginPlay()
{
	Super::BeginPlay();

	InteractableComponent->OnInteractionStart.AddDynamic(this, &ADelivery::InteractionStarted);
	
}

