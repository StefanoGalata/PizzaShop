// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Table.generated.h"

class UInteractableComponent;

UCLASS()
class PIZZASHOP_API ATable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATable();
	
	UFUNCTION()
	virtual void InteractionStarted(ACharacter* InteractingCharacter);

	UFUNCTION()
	virtual void InteractionEnded(ACharacter* InteractingCharacter);

	UFUNCTION(BlueprintCallable, Category = "Table")
	void SetRestingItem(AActor* NewRestingItem);

	UFUNCTION(BlueprintCallable, Category = "Table")
	void RemoveRestingItem();

	UFUNCTION(BlueprintPure, Category = "Table")
	FORCEINLINE AActor* GetRestingItem() { return RestingItem; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemBox")
	USceneComponent* ItemRestLocation;

protected:

	UPROPERTY(EditAnywhere, Category = "ItemBox", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemBox", meta = (AllowPrivateAccess = true))
	UInteractableComponent* InteractableComponent;


	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemBox", meta = (AllowPrivateAccess = true))
	USceneComponent* CustomRootComponent;

	UPROPERTY()
	AActor* RestingItem;

};
