// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	MovementSpeed = 1.f;
	NextMove = EMovementDirection::UP;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();

	AddSnakeElements(4);
}

FVector ASnakeBase::MovementDirToVector(EMovementDirection dir)
{
	static FVector vecs[4]{ FVector(0, -1, 0), FVector(0, 1, 0), FVector(-1, 0, 0), FVector(1, 0, 0) };
	return vecs[static_cast<int>(dir)];
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}

void ASnakeBase::AddSnakeElements(int ElementsNum)
{
	for (int i = 0; i < ElementsNum; i++) {
		FTransform trans(FVector(0, snakeElements.Num() * ElementSize, 0));
		ASnakeElementBase* el = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, trans);//FTransform(/*ElemrntsNum +*/)
		el->init(this, i, EMovementDirection::UP);
		el->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		snakeElements.Add(el);
	}
}

void ASnakeBase::Move(float DeltaTime)
{
	static float step = 0;
	step += DeltaTime / MovementSpeed;
	if (step > 1) {
		step--;
		for (int i = (snakeElements.Num() - 1); i > 0; i--) {
			snakeElements[i]->Position += MovementDirToVector(snakeElements[i]->MovementDirection);
			snakeElements[i]->MovementDirection = snakeElements[i - 1]->MovementDirection;
		}
		snakeElements[0]->Position += MovementDirToVector(snakeElements[0]->MovementDirection);
		snakeElements[0]->MovementDirection = NextMove;
	}
	for (int i = 0; i < snakeElements.Num(); i++)
		snakeElements[i]->SetWorldPosition(step);
	//FVector MoveDelta = DeltaTime / MovementSpeed * ElementSize * MovementDirToVector(LastMove);
	//AddActorWorldOffset(MoveDelta);
}

ASnakeElementBase* ASnakeBase::GetElement(int Range) {
	return snakeElements[Range];
}

