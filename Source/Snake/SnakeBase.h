// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeBase.generated.h"

class ASnakeElementBase;


UENUM()
enum class EMovementDirection {
	UP,
	LEFT,
	DOWN,
	RIGHT
};

UENUM()
enum class EBonuses {
	DEATH,
	ADD,
	POP
};


UCLASS()
class SNAKE_API ASnakeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeBase();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASnakeElementBase> SnakeElementClass;

	UPROPERTY(EditDefaultsOnly)
	float ElementSize;

	UPROPERTY(BlueprintReadWrite)
	float MovementSpeed;
	
	UPROPERTY()
	EMovementDirection NextMove;

	UPROPERTY(BlueprintReadOnly)
	float AllPath;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY()
	TArray<ASnakeElementBase*> snakeElements;

	TArray<FVector> WaitingElements;

	FVector* teleport;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddSnakeElements(int ElemrntsNum = 1);
	void AddSnakeElementWait(int ElemrntsNum = 1);
	void CheckAddElementWait();

	void Move(float DeltaTime);

	ASnakeElementBase* GetElement(int Range);

	FVector MovementDirToVector(EMovementDirection dir);

	void SetMovementDirectory(EMovementDirection dir);

	UFUNCTION()
	void SnakeElementOverlap(ASnakeElementBase* Element, AActor* Other);

	UFUNCTION()
	void AddBonus(EBonuses Bonus, AActor* Other);

	UFUNCTION()
	void Teleport();

};
