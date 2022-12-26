// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"
#include "SnakeBase.h"

// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlock::Interact(AActor* Interactor) {
	/*ASnakeBase* snake = Cast<ASnakeBase>(Interactor);
	if (IsValid(snake))
		snake->AddBonus(EBonuses::DEATH, this);*/
}