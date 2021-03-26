// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeActor.generated.h"

class ASnakeElementBase;

UENUM()
enum class EMovementDirection {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

UCLASS()
class SNAKEGAME_API ASnakeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeActor();

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ASnakeElementBase> SnakeElementClass;
	UPROPERTY(EditDefaultsOnly)
		float ElementSize;
	UPROPERTY(EditDefaultsOnly)
		float MovementSpeed;
	UPROPERTY()
		float NewSpeed;
	UPROPERTY()
		TArray<ASnakeElementBase*> SnakeElements;
	UPROPERTY()
		EMovementDirection LastMoveDirection;
	UPROPERTY()
		FVector SnakeLocation;
	UPROPERTY()
		bool isSpawn;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddSnakeElement(int ElementsNum = 1);

	void Move();

	void AddSpeed();

	UFUNCTION()
		void SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other);
};
