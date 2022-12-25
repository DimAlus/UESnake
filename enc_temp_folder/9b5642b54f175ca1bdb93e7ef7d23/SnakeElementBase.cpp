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
	SinParam = 0.3f;	
	SinAmplitude = 0.1f;
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

float clamp(float a, float min, float max) {
	if (a < min) return min;
	if (a > max) return max;
	return a;
}
float ReAngle(float angle) {
	if (angle) {
	while (angle > 180)
		angle -= 360;
	while (angle < -180)
		angle += 360;

	}
	return angle;
}
void ASnakeElementBase::SetWorldPosition(float path){
	// Point on left-rigth movement
	static float onSin = 2 * PI * SinParam, amplitudeSin = SinAmplitude * ParentSnake->ElementSize;
	float SinMoment = sin(onSin * (ParentSnake->AllPath - Range)) * amplitudeSin;
	// MovementDirection Vector
	FVector MovVector = ParentSnake->MovementDirToVector(MovementDirection);

	FTransform trans = GetActorTransform();

	// Calculating current location
	FVector locat	= (Position + path * MovVector) * ParentSnake->ElementSize;
	locat.Z			= trans.GetLocation().Z;								// Z coordinate is not variable
	locat		   += FVector(MovVector.Y, MovVector.X, 0) * SinMoment;		// Add left-rigth movement

	FVector deltaLoc = locat - trans.GetLocation();
	trans.SetLocation(locat);

	// Calculating current rotation
	// angle  (delta location ^ Vector(0, 1, 0))
	float angle = acos(deltaLoc.Y / sqrt(deltaLoc.X * deltaLoc.X + deltaLoc.Y * deltaLoc.Y));
	// if III or IV location on round
	if (deltaLoc.X > 0) angle = 2 * PI - angle;
	angle = angle / PI * 180 - 180;
	float CurrentAngle = FRotator(trans.GetRotation()).Yaw;
	angle = CurrentAngle + clamp(ReAngle(angle - CurrentAngle), -10, 10);
	//return 2.f * FMath::Acos(W);
	// 
	//float otherAngle = trans.GetRotation().GetAngle() * 2;// / 180 * PI;//.GetTwistAngle(FVector(0, 0, 1));
	//angle = otherAngle + clamp(ReAngle(angle - otherAngle), -0.1, 0.1);
	
	

	//trans.SetRotation(FQuat(FVector(0, 0, 1), angle));//acos(deltaLoc.CosineAngle2D(FVector(0, 1, 0))) / PI * 180)
	trans.SetRotation(FQuat(FRotator(0, angle, 0)));//acos(deltaLoc.CosineAngle2D(FVector(0, 1, 0))) / PI * 180)
	//otherAngle = trans.GetRotation().GetAngle();
//	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("%à"), trans.GetRotation().GetAngle()));
	//float b = trans.GetRotation().GetAngle();
	//trans.SetRotation(FQuat(FVector(0, 0, 1), otherAngle));
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

