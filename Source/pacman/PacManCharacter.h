// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "pacmanGameModeBase.h"
#include "Collectable.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/Classes/Components/CapsuleComponent.h"
#include "Engine/Classes/Components/PrimitiveComponent.h"
#include "Engine/Public/EngineUtils.h"

#include "PacManCharacter.generated.h"

UCLASS()
class PACMAN_API APacManCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	FVector CurrentVelocity;

	// Sets default values for this character's properties
	APacManCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Kill();

private:
	ApacmanGameModeBase* m_GameMode;

	uint8 m_CollectablesToEat; // total collectables in order to win
	uint8 m_Lives; // player total lives


	FVector m_StartPoint; // the start point of the player
	void MoveXAxis(float AxisValue);
	void MoveYAxis(float AxisValue);
	// key events
	void NewGame();
	void Pause();
	void RestartGame();

	UFUNCTION()
		void OnCollision (class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
						
};

