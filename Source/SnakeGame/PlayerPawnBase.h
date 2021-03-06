// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawnBase.generated.h"

class UCameraComponent;
class ASnakeActor;
class AFood;

UCLASS()
class SNAKEGAME_API APlayerPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawnBase();

	UPROPERTY(BluePrintReadWrite)
	UCameraComponent* PawnCamera;
	UPROPERTY(BluePrintReadWrite)
	ASnakeActor* SnakeActor;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASnakeActor> SnakeActorClass;
	UPROPERTY(BluePrintReadWrite)
	AFood* Food;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFood> FoodClass;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CreateSnakeActor();
	void CreateFirstFood();
	
	UFUNCTION()
		void HandlePlayerVerticalInput(float value);
	UFUNCTION()
		void HandlePlayerHorizontalInput(float value);
};
