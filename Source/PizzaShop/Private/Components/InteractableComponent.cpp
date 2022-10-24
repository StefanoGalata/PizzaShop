// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractableComponent.h"
#include "../PizzaShop.h"

UInteractableComponent::UInteractableComponent()
{
	SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetCollisionProfileName(TEXT("Interaction"));
	//SetCollisionObjectType(OBJECT_TYPE_INTERACTABLE);
}
