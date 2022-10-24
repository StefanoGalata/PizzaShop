// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/HoldingItemInterface.h"
#include "Pizza.generated.h"

class UTopping;
class UStaticMeshComponent;

UCLASS()
class PIZZASHOP_API APizza : public AActor, public IHoldingItemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APizza();

	UFUNCTION(BlueprintPure, Category = "Pizza")
	bool IsCooked() const{ return bIsCooked; }

	UFUNCTION(BlueprintCallable, Category = "Pizza")
	void SetIsCooked(bool NewBaked);

	UFUNCTION(BlueprintPure, Category = "Pizza")
	bool IsBoxed() const { return bIsBoxed; }

	UFUNCTION(BlueprintCallable, Category = "Pizza")
	void SetIsBoxed(bool NewBoxed);

	UFUNCTION(BlueprintPure, Category = "Pizza")
	TArray<TSubclassOf<UTopping>>& GetToppings() { return Toppings; }

	UFUNCTION(BlueprintCallable, Category = "Pizza")
	void AddTopping(TSubclassOf<UTopping> ToppingToAdd);

	UFUNCTION(BlueprintPure, Category = "Pizza")
	bool HasTopping(TSubclassOf<UTopping> ToppingToCheck);

	UFUNCTION(BlueprintImplementableEvent, Category = "Pizza")
	void SetCookedMaterial();

	UFUNCTION(BlueprintImplementableEvent, Category = "Pizza")
	void SetBoxedMesh();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pizza")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pizza")
	USceneComponent* CustomRootComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pizza")
	UStaticMesh* BoxedMesh;

	virtual FName GetSocketToAttach_Implementation();

private:
	
	UPROPERTY()
	TArray<TSubclassOf<UTopping>> Toppings;

	bool bIsCooked;

	bool bIsBoxed;
};
