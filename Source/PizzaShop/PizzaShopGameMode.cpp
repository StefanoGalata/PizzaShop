// Copyright Epic Games, Inc. All Rights Reserved.

#include "PizzaShopGameMode.h"
#include "PizzaShopCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Public/Order.h"
#include "Pizza.h"

APizzaShopGameMode::APizzaShopGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	bMatchStarted = false;
	PrimaryActorTick.bCanEverTick = true;
}

void APizzaShopGameMode::AddOrder_Implementation(UOrder* NewOrder)
{
	OngoingOrder = NewOrder;
	OnOngoingOrderAdded.Broadcast(OngoingOrder);
	UE_LOG(LogTemp, Warning, TEXT("Order Toppings: "));
	for (auto& Toppings : OngoingOrder->GetOrderToppings())
	{
		UE_LOG(LogTemp, Warning, TEXT("\t %s"), *Toppings->GetDefaultObject()->GetName() );
	}
}

bool APizzaShopGameMode::HasOngoingOrder_Implementation()
{
	return OngoingOrder != nullptr;
}

bool APizzaShopGameMode::RemoveMatchingOrder(APizza* Pizza)
{
	bool bSucceded = false;
	if(OngoingOrder)
	{
		if (OngoingOrder->Toppings.Num() == Pizza->GetToppings().Num())
		{
			bSucceded = true;
			for (auto& Topping : OngoingOrder->Toppings)
			{
				if (!Pizza->GetToppings().Contains(Topping))
				{
					bSucceded = false;
					break;
				}
			}
			if (bSucceded)
			{
				OnOngoingOrderRemoved.Broadcast(OngoingOrder);
				OngoingOrder = nullptr;
				return true;
			}
		}
	}
	return false;
}

void APizzaShopGameMode::StartMatch()
{
	bMatchStarted = true;
}

void APizzaShopGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bMatchStarted)
	{
		return;
	}
	MatchDurationTime -= DeltaSeconds;
	OnNewTimeSet.Broadcast(MatchDurationTime);
	if (MatchDurationTime < 1.f)
	{
		EndGame();
		SetActorTickEnabled(false);
	}
}

