// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Counter.generated.h"

class UTopping;
class AGameMode;
class UInteractableComponent;

UCLASS()
class PIZZASHOP_API ACounter : public AActor
{
	GENERATED_BODY()
	
public:	
	ACounter();

	UFUNCTION(BlueprintCallable, Category = "Orders")
	void AddOrder();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Counter")
	TArray<TSubclassOf<UTopping>> AllowedToppings;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemBox", meta = (AllowPrivateAccess = true))
	USceneComponent* CustomRootComponent;

	UPROPERTY(EditAnywhere, Category = "ItemBox", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemBox", meta = (AllowPrivateAccess = true))
	UInteractableComponent* InteractableComponent;

	UFUNCTION()
	void InteractionStarted(ACharacter* InteractingCharacter);

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemBox", meta = (AllowPrivateAccess = true))
	USoundBase* AddOrderSound;

	UPROPERTY()
	AGameModeBase* GameMode;

};
