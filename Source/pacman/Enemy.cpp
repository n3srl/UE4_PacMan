// Fill out your copyright notice in the Description page of Project Settings.
#include "Enemy.h"
#include "PacMan.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetActorEnableCollision(true);

	GetCapsuleComponent()->SetCapsuleRadius(40.0f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(50.0f);

	EnemyBody = Cast<USkeletalMeshComponent>(GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	
	// set our custom AI class as controller
	AIControllerClass = AAIEnemy::StaticClass();
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	//get position
	m_SpawnPosition = GetActorLocation();
	// add the collision handler
}

void AEnemy::SetMove(bool moveIt)
{
	// need to cast the AI class and call two public functions from here
	// if false move to its location in order to stop movements
	AAIEnemy* AI = Cast<AAIEnemy>(AIControllerClass);

	if ( AI != NULL )
		if (moveIt) { AI->SearchNewPoint(); }
		else { AI->StopMove(); }
}

void AEnemy::Kill()
{
	// don't kill twice
	if (bIsDead) 
		return;

	// if is not dead, kill and modify its speed
	// the enemy will go fast at his house in order to respawn
	bIsDead = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	AAIEnemy* AI = Cast<AAIEnemy>(AIControllerClass);

	if (AI != NULL)
		AI->GoHome();

}

void AEnemy::Rearm()
{
	bIsDead = false;
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
	if (m_bIsVulnerable) { SetInvulnerable(); }
}

bool AEnemy::IsInvulnerable() {
	return m_bIsVulnerable;
}

void AEnemy::SetVulnerable(float TimeEnemyVulnerable)
{
	// set/reset a timer
	GetWorldTimerManager().SetTimer(m_TimerVulnerable, this,
		&AEnemy::SetInvulnerable, TimeEnemyVulnerable, false);
	// simple return if is already vulnerable
	if (m_bIsVulnerable) { return; }
	m_bIsVulnerable = true;
	// change its material with the transparent one
	
	EnemyBody->SetMaterial(0, VulnerableMaterial);
	// make the enemy run slower
	GetCharacterMovement()->MaxWalkSpeed = 50.0f;
}

// when timer ends, clear it and restore the enemy invulnerability
void AEnemy::SetInvulnerable()
{
	// simple clear the timer
	GetWorldTimerManager().ClearTimer(m_TimerVulnerable);
	m_bIsVulnerable = false;
	// restore the original material
	EnemyBody->SetMaterial(0, DefaultMaterial);
	// restore the original walk speed
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

