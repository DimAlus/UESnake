// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "SnakeBase.h"
#include "Food.generated.h"

UCLASS()
class SNAKE_API AFood : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFood();

	UPROPERTY(EditDefaultsOnly)
	int Helths;

	UPROPERTY(EditDefaultsOnly)
	TArray<EBonuses> Bonuses;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float disableTicks;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* Unteractor) override;

	void Respawn(ASnakeBase* Snake);

	UFUNCTION()
	virtual void Enabling();
	UFUNCTION()
	virtual void Disabling();
};
