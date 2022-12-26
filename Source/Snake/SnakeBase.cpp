// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "Interactable.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	MovementSpeed = 1.f;
	NextMove = EMovementDirection::UP;
	AllPath = 0.f;
	teleport = nullptr;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	
	AddSnakeElements(4);
	
}

FVector ASnakeBase::MovementDirToVector(EMovementDirection dir)
{
	static FVector vecs[4]{ FVector(0, -1, 0), FVector(-1, 0, 0), FVector(0, 1, 0), FVector(1, 0, 0) };
	return vecs[static_cast<int>(dir)];
}
EMovementDirection Radianals(EMovementDirection d) {
	switch (d)
	{
	case EMovementDirection::UP:
		return EMovementDirection::DOWN;
	case EMovementDirection::LEFT:
		return EMovementDirection::RIGHT;
	case EMovementDirection::DOWN:
		return EMovementDirection::UP;
	case EMovementDirection::RIGHT:
		return EMovementDirection::LEFT;
	}
	return EMovementDirection::UP;
}

void ASnakeBase::SetMovementDirectory(EMovementDirection dir){
	if (snakeElements.Num() > 0) {
		if (GetElement(0)->MovementDirection != Radianals(dir))
			NextMove = dir;
	}
	else NextMove = dir;
}

void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* Element, AActor* Other){
	if (IsValid(Element) && !Element->Range) {
		IInteractable* Inter = Cast<IInteractable>(Other);
		if (Inter) {
			Inter->Interact(this);
		}
	}
}

void ASnakeBase::AddBonus(EBonuses Bonus, AActor* Other){
	switch (Bonus)
	{
	case EBonuses::DEATH:
		Destroy();
		break;
	case EBonuses::ADD:
		AddSnakeElementWait();
		break;
	case EBonuses::POP:
		CheckAddElementWait();
		snakeElements.Last()->Destroy();
		snakeElements.RemoveAt(snakeElements.Num() - 1);
		if (snakeElements.Num() < 1)
			AddBonus(EBonuses::DEATH, Other);
		break;
	default:
		break;
	}
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
		int range = snakeElements.Add(el);
		el->init(this, range, range ? GetElement(range - 1)->MovementDirection : NextMove);
		el->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	}
}

void ASnakeBase::AddSnakeElementWait(int ElemrntsNum){
	for (int i = 0; i < ElemrntsNum; i++)
		WaitingElements.Add(snakeElements[0]->Position);
}

void ASnakeBase::CheckAddElementWait(){
	FVector pos = snakeElements.Last()->Position;
	for (int i = WaitingElements.Num() - 1; i >= 0; i--)
		if (pos == WaitingElements[i]) {
			AddSnakeElements();
			WaitingElements.RemoveAt(i);
			pos = snakeElements.Last()->Position;
		}
}

void ASnakeBase::Move(float DeltaTime)
{
	static float step = 0;
	step += DeltaTime / MovementSpeed;
	AllPath += DeltaTime / MovementSpeed;
	if (step > 1) {
		if (teleport) {
			snakeElements[0]->Position = *teleport;
			teleport = nullptr;
		}
		step--;
		CheckAddElementWait();
		for (int i = snakeElements.Num() - 1; i > 0; i--) {
			snakeElements[i]->Position = snakeElements[i - 1]->Position;//MovementDirToVector(snakeElements[i]->MovementDirection);
			snakeElements[i]->MovementDirection = snakeElements[i - 1]->MovementDirection;
		}
		snakeElements[0]->Position += MovementDirToVector(snakeElements[0]->MovementDirection);
		snakeElements[0]->MovementDirection = NextMove;
	}
	for (int i = 0; i < snakeElements.Num(); i++)
		snakeElements[i]->SetWorldPosition(step, DeltaTime);
	for (int i = 1; i < snakeElements.Num(); i++)
		if ((snakeElements[0]->Position == snakeElements[i]->Position))
			AddBonus(EBonuses::DEATH, this);
	//FVector MoveDelta = DeltaTime / MovementSpeed * ElementSize * MovementDirToVector(LastMove);
	//AddActorWorldOffset(MoveDelta);
}

ASnakeElementBase* ASnakeBase::GetElement(int Range) {
	return snakeElements[Range];
}

void ASnakeBase::Teleport(FVector vector) {
	teleport = new FVector(vector);
}

