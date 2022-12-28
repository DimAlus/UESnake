// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Helths = 1;
	disableTicks = -1;
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

	if (disableTicks > 0)
		if ((disableTicks -= DeltaTime) <= 0)
			Enabling();
}

void AFood::Interact(AActor* Interactor){
	ASnakeBase* snake = Cast<ASnakeBase>(Interactor);
	if (IsValid(snake)) {
		if (--Helths <= 0) {
			for (int i = 0; i < Bonuses.Num(); i++)
				snake->AddBonus(Bonuses[i], this);
			Destroy();
		}
		else {
			disableTicks = 1.f;
			Disabling();
		}
	}

}

void AFood::Respawn(ASnakeBase* Snake){
	
}

void AFood::Enabling() {
	SetActorEnableCollision(true);
}


void AFood::Disabling() {
	SetActorEnableCollision(false);
}
