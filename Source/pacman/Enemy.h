// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIEnemy.h"
#include "PacManCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavigationSystem/Public/NavigationSystem.h"

#include "Enemy.generated.h"

UCLASS()
class PACMAN_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void OnCollision(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = Body)
		UStaticMeshComponent* EnemyBody;
	void SetVulnerable();
	void SetInvulnerable();
	void SetMove(bool MoveIt);
	void Kill();
	void Rearm();
	
	bool bIsDead;

private:
	bool m_bIsVulnerable;
	FTimerHandle m_TimerVulnerable;
	class UMaterialInterface* m_DefaultMaterial;
	class UMaterialInterface* m_VulnerableMaterial;

};
