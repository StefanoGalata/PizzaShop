// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/HoldingItemInterface.h"
#include "ToppingActor.generated.h"

class UTopping;

UCLASS()
class PIZZASHOP_API AToppingActor : public AActor, public IHoldingItemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AToppingActor();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UTopping> Topping;

	virtual FName GetSocketToAttach_Implementation();


};
