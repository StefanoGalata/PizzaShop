// Copyright Epic Games, Inc. All Rights Reserved.

#include "PizzaShopCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/InteractionSphereComponent.h"
#include "PizzaShop.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/HoldingItemInterface.h"

APizzaShopCharacter::APizzaShopCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	InteractionSphere = CreateDefaultSubobject<UInteractionSphereComponent>(TEXT("Interaction Sphere"));
	InteractionSphere->SetupAttachment(GetMesh());
	
	HoldingItem = nullptr;
}

void APizzaShopCharacter::SetHoldingItem(AActor* NewHoldingItem)
{
	if(!HoldingItem)
	{
		HoldingItem = NewHoldingItem;
		FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, true);
		FName SocketToAttachName = TEXT("PizzaSocket");
		if (HoldingItem->GetClass()->ImplementsInterface(UHoldingItemInterface::StaticClass()))
		{
			SocketToAttachName = IHoldingItemInterface::Execute_GetSocketToAttach(HoldingItem);
		}
		HoldingItem->AttachToComponent(GetMesh(), AttachRules, SocketToAttachName);

		OnNewItemHeld.Broadcast(HoldingItem);
	}

}

void APizzaShopCharacter::RemoveHoldingItem()
{
	HoldingItem->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	HoldingItem = nullptr;
	OnNewItemHeld.Broadcast(nullptr);
}

void APizzaShopCharacter::AddScore(float Score)
{
	GetPlayerState()->SetScore(GetPlayerState()->GetScore() + Score);
	OnNewScoreSet.Broadcast(GetPlayerState()->GetScore());
}

void APizzaShopCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APizzaShopCharacter::Interact);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &APizzaShopCharacter::StopInteraction);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &APizzaShopCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &APizzaShopCharacter::MoveRight);

}

void APizzaShopCharacter::Interact()
{
	if (InteractionSphere)
	{
		InteractionSphere->Interact();
	}

}

void APizzaShopCharacter::StopInteraction()
{
	if (InteractionSphere)
	{
		InteractionSphere->EndInteraction();
	}
}

void APizzaShopCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APizzaShopCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
