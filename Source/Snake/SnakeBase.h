// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeBase.generated.h"

class ASnakeElementBase;


UENUM()
enum class EMovementDirection {
	UP,
	DOWN,
	LEFT,
	RIGHT
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

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddSnakeElements(int ElemrntsNum = 1);

	void Move(float DeltaTime);

	ASnakeElementBase* GetElement(int Range);

	FVector MovementDirToVector(EMovementDirection dir);
};
