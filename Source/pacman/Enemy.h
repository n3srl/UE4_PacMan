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

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void SetVulnerable(float TimeEnemyVulnerable);

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void SetInvulnerable();
	
	UFUNCTION(BlueprintCallable, Category = "Enemy")
	bool IsInvulnerable();

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void SetMove(bool MoveIt);

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void Kill();

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void Rearm();
	
	bool bIsDead;

	

	UPROPERTY(EditAnywhere, Category = Body)
	class UMaterialInterface* DefaultMaterial;

	UPROPERTY(EditAnywhere, Category = Body)
	class UMaterialInterface* VulnerableMaterial;

	UPROPERTY(EditAnywhere, Category = Body)
	USkeletalMeshComponent* EnemyBody;

private:
	bool m_bIsVulnerable;
	FTimerHandle m_TimerVulnerable;
	FVector m_SpawnPosition;

};
