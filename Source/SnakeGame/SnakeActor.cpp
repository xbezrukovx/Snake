// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeActor.h"
#include "SnakeElementBase.h"
#include "Interactable.h"
// Sets default values
ASnakeActor::ASnakeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	MovementSpeed = 0,500.f;
	LastMoveDirection = EMovementDirection::DOWN;
}

// Called when the game starts or when spawned
void ASnakeActor::BeginPlay()
{
	NewSpeed = MovementSpeed;
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed);
	isSpawn = true;
	AddSnakeElement(3);
	isSpawn = false;
}

// Called every frame
void ASnakeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void ASnakeActor::AddSnakeElement(int ElementsNum){
	for (int i = 0; i < ElementsNum; ++i) {
		if (isSpawn) {
			FVector NewLocation(480, 0, 0);
			FTransform NewTransform(NewLocation);
			ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
			NewSnakeElem->SnakeOwner = this;
			int32 ElemIndex = SnakeElements.Add(NewSnakeElem);
			if (ElemIndex == 0) {
				NewSnakeElem->SetFirstElementType();
			}
		}
		else{ 
			FVector NewLocation(SnakeElements.Num() * ElementSize, 0, -90);
			FTransform NewTransform(NewLocation);
			ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
			NewSnakeElem->SnakeOwner = this;
			int32 ElemIndex = SnakeElements.Add(NewSnakeElem);
			if (ElemIndex == 0) {
				NewSnakeElem->SetFirstElementType();
			}
		}
	}
}

void ASnakeActor::Move()
{
	FVector MovementVector(ForceInitToZero);
	MovementSpeed = ElementSize;

	switch (LastMoveDirection){
	case EMovementDirection::UP:
		MovementVector.X += MovementSpeed;
		break;
	case EMovementDirection::DOWN:
		MovementVector.X -= MovementSpeed;
		break;
	case EMovementDirection::LEFT:
		MovementVector.Y += MovementSpeed;
		break;
	case EMovementDirection::RIGHT:
		MovementVector.Y -= MovementSpeed;
		break;
	}

	SnakeElements[0]->ToggleCollision();

	for (int i = SnakeElements.Num() - 1; i > 0; i--) {
		auto CurrentElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i - 1];
		FVector PrevLocation = PrevElement->GetActorLocation();
		CurrentElement->SetActorLocation(PrevLocation);
	}

	SnakeLocation = SnakeElements[0]->GetActorLocation();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(SnakeLocation.X));

	if (SnakeLocation.X > 480 || SnakeLocation.X < -480) {
		SnakeLocation.X *= -1;
		SnakeElements[0]->SetActorLocation(SnakeLocation);
	}
	if (SnakeLocation.Y > 480 || SnakeLocation.Y < -480) {
		SnakeLocation.Y *= -1;
		SnakeElements[0]->SetActorLocation(SnakeLocation);
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCollision();
}

void ASnakeActor::AddSpeed()
{
	if(NewSpeed > 0.125) NewSpeed = NewSpeed - 0.010;
	SetActorTickInterval(NewSpeed);
}

void ASnakeActor::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other)
{
	if (IsValid(OverlappedElement)) {
		int32 ElemIndex;
		SnakeElements.Find(OverlappedElement, ElemIndex);
		bool BeIsFirst = ElemIndex == 0;
		IInteractable* InteractableInterface = Cast<IInteractable>(Other);
		if (InteractableInterface) {
			InteractableInterface->Interact(this, BeIsFirst);
		}
	}
}

