// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "SnakeElementBase.generated.h"

class UStaticMeshComponent;
enum class EMovementDirection;
class ASnakeBase;

UCLASS()
class SNAKE_API ASnakeElementBase : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeElementBase();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
	EMovementDirection MovementDirection;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
	ASnakeBase* ParentSnake;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
	FVector Position;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
	int Range;

	UPROPERTY(EditDefaultsOnly)
	float SinParam;

	UPROPERTY(EditDefaultsOnly)
	float SinAmplitude;

	UPROPERTY(EditDefaultsOnly)
	float RotatePerSecond;

	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* vertebra;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetWorldPosition(float path, float deltaTime);

	void SetWorldRotation(EMovementDirection dir);

	void init(ASnakeBase* parentSnake, int range, EMovementDirection movementDirection);

	UFUNCTION(BlueprintNativeEvent)
	void SetSnakeHead();
	void SetSnakeHead_Implementation();

	virtual void Interact(AActor* Interactor);

	UFUNCTION()
	void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other,
								UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
								bool bFromSweep, const FHitResult& SweepResult);
};
