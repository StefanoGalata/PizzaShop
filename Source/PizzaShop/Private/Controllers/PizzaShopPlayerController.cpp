// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/PizzaShopPlayerController.h"
#include "../../PizzaShopGameMode.h"
#include "Widgets/MainHUD.h"
#include "Kismet/GameplayStatics.h"
#include "../PizzaShopCharacter.h"

void APizzaShopPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MainHud = CreateWidget<UMainHUD>(this, MainHudClass, "MainHUD");
	if (MainHud)
	{
		MainHud->AddToViewport();
	}

	APizzaShopGameMode* PizzaShopGameMode = Cast<APizzaShopGameMode>(UGameplayStatics::GetGameMode(this));
	if (PizzaShopGameMode)
	{
		PizzaShopGameMode->OnOngoingOrderAdded.AddDynamic(this, &APizzaShopPlayerController::OrderAdded);
		PizzaShopGameMode->OnOngoingOrderRemoved.AddDynamic(this, &APizzaShopPlayerController::OrderRemoved);
		PizzaShopGameMode->OnNewTimeSet.AddDynamic(this, &APizzaShopPlayerController::SetNewTime);
	}
}


void APizzaShopPlayerController::OrderAdded(UOrder* NewOrder)
{
	if (MainHud)
	{
		MainHud->SetOngoingOrder(NewOrder);
	}
}

void APizzaShopPlayerController::OrderRemoved(UOrder* RemovedOrder)
{
	if (MainHud)
	{
		MainHud->RemoveOngoingOrder();
	}
}

void APizzaShopPlayerController::SetNewTime(float NewTime)
{
	if (MainHud)
	{
		MainHud->SetTimeUI(FMath::FloorToInt32(NewTime));
	}
}

void APizzaShopPlayerController::SetScoreInHud(float NewScore)
{
	if (MainHud)
	{
		MainHud->SetScoreUI(NewScore);
	}
}

void APizzaShopPlayerController::OnPossessedPawnNewItemHeld(AActor* NewItem)
{
	if (MainHud)
	{
		MainHud->SetPlayerHoldingItemUI(NewItem);
	}
}

void APizzaShopPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	APizzaShopCharacter* PizzaShopCharacter = Cast<APizzaShopCharacter>(InPawn);

	if (PizzaShopCharacter)
	{
		PizzaShopCharacter->OnNewItemHeld.AddUniqueDynamic(this, &APizzaShopPlayerController::OnPossessedPawnNewItemHeld);
		PizzaShopCharacter->OnNewScoreSet.AddUniqueDynamic(this, &APizzaShopPlayerController::SetScoreInHud);
	}
}
