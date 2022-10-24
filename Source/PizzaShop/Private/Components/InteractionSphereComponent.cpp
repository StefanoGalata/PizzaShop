// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionSphereComponent.h"
#include "Components/InteractableComponent.h"
#include "../PizzaShop.h"
#include "GameFramework/Character.h"

UInteractionSphereComponent::UInteractionSphereComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetCollisionProfileName(TEXT("Interaction"));

}

void UInteractionSphereComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GetOverlappingComponents(OverlappingComponents);

	if (OverlappingComponents.Num() > 0)
	{
		CurrentFocusedInteractable = Cast<UInteractableComponent>(OverlappingComponents[0]);
	}
	else
	{
		CurrentFocusedInteractable = nullptr;
	}
}

void UInteractionSphereComponent::Interact()
{
	if (CurrentFocusedInteractable)
	{
		CurrentFocusedInteractable->OnInteractionStart.Broadcast(Cast<ACharacter>(GetOwner()));
	}
}

void UInteractionSphereComponent::EndInteraction()
{
	if (CurrentFocusedInteractable)
	{
		CurrentFocusedInteractable->OnInteractionEnd.Broadcast(Cast<ACharacter>(GetOwner()));
	}
}
