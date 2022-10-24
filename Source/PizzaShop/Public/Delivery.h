// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Delivery.generated.h"

class APizza;
class UInteractableComponent;

UCLASS()
class PIZZASHOP_API ADelivery : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADelivery();

	UFUNCTION()
	virtual void InteractionStarted(ACharacter* InteractingCharacter);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemBox", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemBox", meta = (AllowPrivateAccess = true))
	UInteractableComponent* InteractableComponent;

private:


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemBox", meta = (AllowPrivateAccess = true))
	USoundBase* DeliverySound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemBox", meta = (AllowPrivateAccess = true))
	USceneComponent* CustomRootComponent;

	bool RemoveMatchingOrder(APizza* Pizza);

};
