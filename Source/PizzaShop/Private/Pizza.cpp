// Fill out your copyright notice in the Description page of Project Settings.


#include "Pizza.h"
#include "Toppings/Topping.h"

// Sets default values
APizza::APizza()
{
	PrimaryActorTick.bCanEverTick = false;

	CustomRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Custom Root Comp"));
	CustomRootComp->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CustomRootComp);

	bIsCooked = false;
	bIsBoxed = false;

}

FName APizza::GetSocketToAttach_Implementation()
{
	if (bIsBoxed)
	{
		return TEXT("PizzaBoxedSocket");
	}
	return TEXT("PizzaSocket");
}

void APizza::SetIsCooked(bool NewCooked)
{
	bIsCooked = NewCooked;
	SetCookedMaterial();
}

void APizza::SetIsBoxed(bool NewBoxed)
{
	bIsBoxed = NewBoxed;
	SetBoxedMesh();
}

void APizza::AddTopping(TSubclassOf<UTopping> ToppingToAdd)
{
	if (ToppingToAdd != nullptr && !Toppings.Contains(ToppingToAdd) )
	{
		Toppings.Add(ToppingToAdd);
	}
}

bool APizza::HasTopping(TSubclassOf<UTopping> ToppingToCheck)
{
	for (auto& Topping : Toppings)
	{
		if (*Topping == *ToppingToCheck)
		{
			return true;
		}
	}
	return false;
}

