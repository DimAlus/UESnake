// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"

#include "Teleport.generated.h"

UCLASS()
class SNAKE_API ATeleport : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleport();

	UPROPERTY(EditDefaultsOnly)
	int IndexTeleport;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	static TArray<ATeleport*> teleports;

	float timerDisable = -1.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact(AActor* Interactor) override;

	UFUNCTION()
	void Enable();

	UFUNCTION()
	void Disable();
};
