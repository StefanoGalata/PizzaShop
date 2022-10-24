// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "InteractionSphereComponent.generated.h"

class UInteractableComponent;

UCLASS()
class PIZZASHOP_API UInteractionSphereComponent : public USphereComponent
{
	GENERATED_BODY()

public:

	UInteractionSphereComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

	void Interact();
	void EndInteraction();

protected:
	UPROPERTY(BlueprintReadOnly, Category = Interaction)
	UInteractableComponent* CurrentFocusedInteractable;

private:
	UPROPERTY()
	TArray< UPrimitiveComponent* > OverlappingComponents;
};
