// Fill out your copyright notice in the Description page of Project Settings.


#include "Counter.h"
#include "Components/InteractableComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Toppings/Pepperoni.h"
#include "Order.h"
#include "GameFramework/GameMode.h"
#include "Interfaces/RulesInterface.h"

// Sets default values
ACounter::ACounter()
{
	PrimaryActorTick.bCanEverTick = false;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Custom Root"));
	CustomRootComponent->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CustomRootComponent);

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable Component"));
	InteractableComponent->SetupAttachment(CustomRootComponent);
}

void ACounter::AddOrder()
{
	if (GameMode->GetClass()->ImplementsInterface(URulesInterface::StaticClass()))
	{
		if (GameMode && !IRulesInterface::Execute_HasOngoingOrder(GameMode))
		{
			UOrder* Order = NewObject<UOrder>();
			Order->Toppings.Add(AllowedToppings[FMath::RandRange(0, AllowedToppings.Num()-1)]);
			IRulesInterface::Execute_AddOrder(GameMode, Order);
			if (AddOrderSound)
			{
				UGameplayStatics::PlaySound2D(this, AddOrderSound);
			}
		}
	}
}

void ACounter::InteractionStarted(ACharacter* InteractingCharacter)
{
	AddOrder();
}

// Called when the game starts or when spawned
void ACounter::BeginPlay()
{
	Super::BeginPlay();
	
	InteractableComponent->OnInteractionStart.AddDynamic(this, &ACounter::InteractionStarted);
	GameMode = UGameplayStatics::GetGameMode(GetWorld());
}

