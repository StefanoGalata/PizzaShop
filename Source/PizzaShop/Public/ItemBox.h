// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBox.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemGenerated, AActor*, GeneratedItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemRemoved, AActor*, RemovedItem);

class UWidgetComponent;
class UInteractableComponent;

UCLASS()
class PIZZASHOP_API AItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBox();

	UFUNCTION(BlueprintCallable)
	virtual void GenerateItem();

	UFUNCTION(BlueprintCallable)
	virtual void StartItemGeneration();

	UFUNCTION(BlueprintCallable)
	virtual void PauseItemGeneration();

	UFUNCTION(BlueprintCallable)
	void RemoveSpanwedItem();

	UFUNCTION()
	virtual void ItemGenerated(AActor* GeneratedItem);


	UFUNCTION()
	virtual void InteractionStarted(ACharacter* InteractingCharacter);

	UFUNCTION()
	virtual void InteractionEnded(ACharacter* InteractingCharacter);
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE AActor* GetItem() { return NewItem; }

	UFUNCTION(BlueprintPure, Category="ItemBox")
	FORCEINLINE float GetCurrentGenerationTime() const {return CurrentGenerationTime;}

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FOnItemGenerated OnItemGenerated;

	UPROPERTY(BlueprintAssignable)
	FOnItemRemoved OnItemRemoved;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "ItemBox")
	TSubclassOf<AActor> ItemToGenerate;

	UPROPERTY(EditAnywhere, Category = "ItemBox")
	USceneComponent* ItemSpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemBox")
	UWidgetComponent* ProgressionWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemBox")
	float TimeToGenerateItem = 0.f;

	UPROPERTY()
	AActor* NewItem;


	UPROPERTY(EditAnywhere, Category = "ItemBox", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemBox", meta = (AllowPrivateAccess = true))
	UInteractableComponent* InteractableComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemBox", meta = (AllowPrivateAccess = true))
	USceneComponent* CustomRootComponent;

	UPROPERTY(EditAnywhere, Category = "ItemBox|Sounds")
	USoundBase* ItemStartGenerationSound;

	UPROPERTY(EditAnywhere, Category = "ItemBox|Sounds")
	USoundBase* ItemGeneratedSound;

	UPROPERTY()
	UAudioComponent* ItemStartGenerationSoundComponent;

private:

	float CurrentGenerationTime;
};
