// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "InteractableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteraction, ACharacter*, InteractingCharacter);

UCLASS()
class PIZZASHOP_API UInteractableComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	UInteractableComponent();

	UPROPERTY(BlueprintAssignable)
	FOnInteraction OnInteractionStart;

	UPROPERTY(BlueprintAssignable)
	FOnInteraction OnInteractionEnd;
	
};
