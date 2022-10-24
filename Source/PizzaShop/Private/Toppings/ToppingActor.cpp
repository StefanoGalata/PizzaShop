// Fill out your copyright notice in the Description page of Project Settings.


#include "Toppings/ToppingActor.h"

// Sets default values
AToppingActor::AToppingActor()
{
	PrimaryActorTick.bCanEverTick = false;

}

FName AToppingActor::GetSocketToAttach_Implementation()
{
	return TEXT("ToppingSocket");
}

