// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBox.h"
#include "Components/InteractableComponent.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "../PizzaShopCharacter.h"
#include "Widgets/ProgressionWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

// Sets default values
AItemBox::AItemBox()
{
	PrimaryActorTick.bCanEverTick = true;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Custom Root"));
	CustomRootComponent->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CustomRootComponent);

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable Component"));
	InteractableComponent->SetupAttachment(CustomRootComponent);

	ItemSpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Item Spawn Location"));
	ItemSpawnLocation->SetupAttachment(CustomRootComponent);

	ProgressionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Progression Widget"));
	ProgressionWidget->SetupAttachment(CustomRootComponent);
	ProgressionWidget->SetRelativeLocation(FVector(50, 5, 161));
	ProgressionWidget->SetRelativeRotation(FRotator(90, 10, -80));
	ProgressionWidget->SetDrawSize(FVector2D(100,20));
	CurrentGenerationTime = 0.f;
}

void AItemBox::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
	ProgressionWidget->SetVisibility(false);

	InteractableComponent->OnInteractionStart.AddDynamic(this, &AItemBox::InteractionStarted);
	InteractableComponent->OnInteractionEnd.AddDynamic(this, &AItemBox::InteractionEnded);

	OnItemGenerated.AddDynamic(this, &AItemBox::ItemGenerated);
}

void AItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentGenerationTime += DeltaTime;
	if (UProgressionWidget* Widget = Cast<UProgressionWidget>(ProgressionWidget->GetWidget()))
	{
		Widget->SetWidgetProgression(CurrentGenerationTime/TimeToGenerateItem);
	}
	UE_LOG(LogTemp, Warning, TEXT("CurrentGenerationTime: %f"), CurrentGenerationTime);
	if (CurrentGenerationTime >= TimeToGenerateItem)
	{
		GenerateItem();
		CurrentGenerationTime = 0.f;
		SetActorTickEnabled(false);
	}
}

void AItemBox::GenerateItem()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	NewItem = GetWorld()->SpawnActor<AActor>(ItemToGenerate, ItemSpawnLocation->GetComponentLocation(), ItemSpawnLocation->GetComponentRotation(), SpawnParameters);
	OnItemGenerated.Broadcast(NewItem);
	if (ItemStartGenerationSoundComponent)
	{
		ItemStartGenerationSoundComponent->Stop();
		ItemStartGenerationSoundComponent->DestroyComponent();
		ItemStartGenerationSoundComponent = nullptr;
	}
	if (ItemGeneratedSound)
	{
		UGameplayStatics::PlaySound2D(this, ItemGeneratedSound);
	}
}

void AItemBox::StartItemGeneration()
{
	if (TimeToGenerateItem <= 0.f)
	{
		GenerateItem();
	}

	else
	{
		ProgressionWidget->SetVisibility(true);
		SetActorTickEnabled(true);
		if (ItemStartGenerationSoundComponent)
		{
			ItemStartGenerationSoundComponent->SetPaused(false);
		}
		else if (ItemStartGenerationSound)
		{
			ItemStartGenerationSoundComponent = UGameplayStatics::SpawnSound2D(this, ItemStartGenerationSound, 1.f, 1.f, 0.f, nullptr, false, false);
			ItemStartGenerationSoundComponent->Play();
		}
	}
}

void AItemBox::PauseItemGeneration()
{
	SetActorTickEnabled(false);
	if (ItemStartGenerationSoundComponent)
	{
		ItemStartGenerationSoundComponent->SetPaused(true);
	}
}

void AItemBox::RemoveSpanwedItem()
{
	OnItemRemoved.Broadcast(NewItem);
	NewItem = nullptr;
}

void AItemBox::ItemGenerated(AActor* GeneratedItem)
{
	ProgressionWidget->SetVisibility(false);
}

void AItemBox::InteractionStarted(ACharacter* InteractingCharacter)
{
	if (!GetItem())
	{
		StartItemGeneration();
	}
	else
	{
		APizzaShopCharacter* PizzaShopCharacter = Cast<APizzaShopCharacter>(InteractingCharacter);
		if (PizzaShopCharacter)
		{
			if (PizzaShopCharacter->GetHoldingItem() == nullptr)
			{
				PizzaShopCharacter->SetHoldingItem(GetItem());
				RemoveSpanwedItem();
			}
		}
	}
}

void AItemBox::InteractionEnded(ACharacter* InteractingCharacter)
{
	PauseItemGeneration();
}

