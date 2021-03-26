// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "SnakeActor.h"

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

void AFood::Interact(AActor* Interactor, bool BeIsHead)
{
	if (BeIsHead) {
		auto Snake = Cast<ASnakeActor>(Interactor);
		if (IsValid(Snake)) {
			CreateNewFood(1);
			Snake->AddSnakeElement();
			Snake->AddSpeed();
			Destroy();
		}
	}
}

void AFood::CreateNewFood(int countFood) {
	for (int i = 0; i < countFood; i++) {
		NewLocation.X = rand() % 960 - 480;
		NewLocation.Y = rand() % 960 - 480;
		NewLocation.Z = 10;
		FTransform NewTransform(NewLocation);
		GetWorld()->SpawnActor<AFood>(FoodClass, NewTransform);
	}
}