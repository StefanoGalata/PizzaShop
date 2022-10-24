// Fill out your copyright notice in the Description page of Project Settings.


#include "Bin.h"
#include <Components/InteractableComponent.h>
#include <../PizzaShopCharacter.h>
#include "Kismet/GameplayStatics.h"

// Sets default values
ABin::ABin()
{
 	PrimaryActorTick.bCanEverTick = false;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Custom Root"));
	CustomRootComponent->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CustomRootComponent);

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable Component"));
	InteractableComponent->SetupAttachment(CustomRootComponent);
}


// Called when the game starts or when spawned
void ABin::BeginPlay()
{
	Super::BeginPlay();
	
	InteractableComponent->OnInteractionStart.AddDynamic(this, &ABin::InteractionStarted);
}

void ABin::InteractionStarted(ACharacter* InteractingCharacter)
{
	APizzaShopCharacter* PizzaShopCharacter = Cast<APizzaShopCharacter>(InteractingCharacter);
	if (!PizzaShopCharacter || PizzaShopCharacter->GetHoldingItem() == nullptr)
	{
		return;
	}
	AActor* ItemToDestroy = PizzaShopCharacter->GetHoldingItem();
	PizzaShopCharacter->RemoveHoldingItem();
	ItemToDestroy->Destroy();
	if (ItemDestroyedSound)
	{
		UGameplayStatics::PlaySound2D(this, ItemDestroyedSound);
	}
}

