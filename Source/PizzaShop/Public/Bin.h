// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bin.generated.h"

class UInteractableComponent;

UCLASS()
class PIZZASHOP_API ABin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABin();

	UFUNCTION()
	void InteractionStarted(ACharacter* InteractingCharacter);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bin", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bin", meta = (AllowPrivateAccess = true))
	UInteractableComponent* InteractableComponent;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bin", meta = (AllowPrivateAccess = true))
	USceneComponent* CustomRootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bin", meta = (AllowPrivateAccess = true))
	USoundBase* ItemDestroyedSound;


};
