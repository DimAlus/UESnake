// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeElementBase.h"
#include "SnakeBase.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values
ASnakeElementBase::ASnakeElementBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SinParam = 0.f;	
}

// Called when the game starts or when spawned
void ASnakeElementBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASnakeElementBase::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

void ASnakeElementBase::SetWorldPosition(float path){
	FTransform trans = GetActorTransform();
	FVector locat = (Position + path * ParentSnake->MovementDirToVector(MovementDirection)) * ParentSnake->ElementSize;
	locat.Z = trans.GetLocation().Z;
	FVector deltaLoc = locat - trans.GetLocation();
	float angle = deltaLoc.Y / sqrt(deltaLoc.X * deltaLoc.X + deltaLoc.Y * deltaLoc.Y);
	trans.SetLocation(locat);
	//(0, 1, 0)
	trans.SetRotation(FQuat(FVector(0, 0, 1), acos(angle) * (deltaLoc.X > 0 ? 1 : -1)));//acos(deltaLoc.CosineAngle2D(FVector(0, 1, 0))) / PI * 180)
	SetActorTransform(trans);
}

void ASnakeElementBase::init(ASnakeBase* parentSnake, int range, EMovementDirection movementDirection){
	MovementDirection = movementDirection;
	Range = range;
	ParentSnake = parentSnake;
	if (range)
		Position = ParentSnake->GetElement(range - 1)->Position - ParentSnake->MovementDirToVector(movementDirection);
	else
		Position = FVector();
	SetWorldPosition(0);
}

