// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Helths = 1;
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFood::Interact(AActor* Interactor){
	ASnakeBase* snake = Cast<ASnakeBase>(Interactor);
	if (IsValid(snake)) {
		if (--Helths <= 0) {
			for (int i = 0; i < Bonuses.Num(); i++)
				snake->AddBonus(Bonuses[i], this);
			Destroy();
		}
	}

}

