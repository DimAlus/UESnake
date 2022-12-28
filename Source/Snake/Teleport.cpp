#include "Teleport.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleport.h"
#include "SnakeBase.h"

// Sets default values
ATeleport::ATeleport()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATeleport::BeginPlay()
{
	Super::BeginPlay();
	//teleports.push_back(this);
}

// Called every frame
void ATeleport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (timerDisable > 0) {
		if ((timerDisable -= DeltaTime) < 0)
			Enable();
	}
}

void ATeleport::Interact(AActor* Interactor){
	ASnakeBase* snake = Cast<ASnakeBase>(Interactor);
	if (IsValid(snake)) snake->Teleport();
		// for (int i = 0; i < teleports.Num(); i++)
		// 	if (teleports[i] != this && teleports[i]->IndexTeleport == IndexTeleport) {
		// 		FVector loc = teleports[i]->GetActorLocation() / snake->ElementSize;
		// 		snake->Teleport(FVector(round(loc.X), round(loc.Y), round(loc.Z)));
		// 		Disable();
		// 		teleports[i]->Disable();
		// 		break;
		// 	}
	
}

void ATeleport::Enable() {
	SetActorEnableCollision(true);
}

void ATeleport::Disable() {
	timerDisable = 10;
	SetActorEnableCollision(false);
}
