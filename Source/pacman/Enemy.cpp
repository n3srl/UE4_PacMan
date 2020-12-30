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

	// add a cylinder shape to the enemy and set its size
	//static ConstructorHelpers::FObjectFinder<UStaticMesh>CylinderObj
	//(TEXT("'/Game/StarterContent/Shapes/Shape_Cylinder'"));
	EnemyBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	//EnemyBody->SetStaticMesh( CylinderObj.Object );
	//EnemyBody->SetRelativeScale3D(FVector(0.7f, 0.7f, 1.0f));
	EnemyBody->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	// set the vulnerable material, same for all the enemies
	static ConstructorHelpers::FObjectFinder<UMaterial>	VulnerableMat(TEXT("Material'/Game/Materials/M_enemies_vulnerable.M_enemies_vulnerable'"));

	if (VulnerableMat.Object != NULL)
	{
		m_VulnerableMaterial = VulnerableMat.Object;
	}

	// set our custom AI class as controller
	AIControllerClass = AAIEnemy::StaticClass();
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	m_DefaultMaterial = EnemyBody->GetMaterial(0);
	// add the collision handler
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic (this, &AEnemy::OnCollision);
}

void AEnemy::SetMove(bool moveIt)
{
	// need to cast the AI class and call two public functions from here
	// if false move to its location in order to stop movements
	AAIEnemy* AI = Cast<AAIEnemy>(AIControllerClass);

	if (moveIt) { AI->SearchNewPoint(); }
	else { AI->StopMove(); }

}

void AEnemy::Kill()
{
	// don't kill twice
	if (bIsDead) return;
	// if is not dead, kill and modify its speed
	// the enemy will go fast at his house in order to respawn
	bIsDead = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void AEnemy::Rearm()
{
	bIsDead = false;
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
	if (m_bIsVulnerable) { SetInvulnerable(); }
}

void AEnemy::SetVulnerable()
{
	// set/reset a timer
	GetWorldTimerManager().SetTimer(m_TimerVulnerable, this,
		&AEnemy::SetInvulnerable, 10.0f, false);
	// simple return if is already vulnerable
	if (m_bIsVulnerable) { return; }
	m_bIsVulnerable = true;
	// change its material with the transparent one

	EnemyBody->SetMaterial(0, m_VulnerableMaterial);
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
	EnemyBody->SetMaterial(0, m_DefaultMaterial);
	// restore the original walk speed
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
}

void AEnemy::OnCollision(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APacManCharacter::StaticClass()))
	{
		// check whenever the pawn is vulnerable or not
		// simple kill it if is vulnerable
		if (m_bIsVulnerable) { Kill(); }
		else
		{
			// or kill the player instead if not
			APacManCharacter* PacMan =
				Cast<APacManCharacter>(OtherActor);
			PacMan->Kill();
		}
	}
}


// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

