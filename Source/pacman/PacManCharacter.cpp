// Fill out your copyright notice in the Description page of Project Settings.
#include "PacManCharacter.h"

// Sets default values
APacManCharacter::APacManCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetActorEnableCollision(true);
	bUseControllerRotationYaw = false;

	//Set collider
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APacManCharacter::OnCollision);
	//Add particle
	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));

}

// Called when the game starts or when spawned
void APacManCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_GameMode = Cast<ApacmanGameModeBase>(UGameplayStatics::GetGameMode(this));
	

	m_StartPoint = GetActorLocation(); // simple get the player location
	Lives = 3; // set the full life when start
}

void APacManCharacter::OnCollision(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACollectable* collectable = Cast<ACollectable>(OtherActor);

	if (collectable != nullptr)
		if (m_GameMode->GetCurrentState() == EGameState::EPlaying) {
			m_GameMode->EatCollectible();
		}
}

FString APacManCharacter::GetLives() {
	return FString(""+Lives);
}


void APacManCharacter::Pause()
{
	if (m_GameMode->GetCurrentState() == EGameState::EPlaying) {
		m_GameMode->SetCurrentState(EGameState::EPause);
	}

	else if (m_GameMode->GetCurrentState() == EGameState::EPause) {
		m_GameMode->SetCurrentState(EGameState::EPlaying);
	}
}

void APacManCharacter::RestartGame()
{
	GetWorld()->GetFirstPlayerController()->
	ConsoleCommand(TEXT("RestartLevel"));
}

void APacManCharacter::NewGame()
{
	if (m_GameMode->GetCurrentState() == EGameState::EMenu) {
		m_GameMode->SetCurrentState(EGameState::EPlaying);
	}
}

// Called every frame
void APacManCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APacManCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveX", this, &APacManCharacter::MoveXAxis);
	InputComponent->BindAxis("MoveY", this, &APacManCharacter::MoveYAxis);
	InputComponent->BindAction("NewGame", IE_Pressed, this, &APacManCharacter::NewGame);
	InputComponent->BindAction("Pause", IE_Pressed, this, &APacManCharacter::Pause);
	InputComponent->BindAction("Restart", IE_Pressed, this,	&APacManCharacter::RestartGame);
}

void APacManCharacter::MoveXAxis(float AxisValue)
{
	if (AxisValue) {
		CurrentVelocity.X = AxisValue;

		AddMovementInput( CurrentVelocity );

		FRotator Rotation = GetRotation(CurrentVelocity);

		SetActorRotation(Rotation);
	}
	else
		CurrentVelocity.X = 0;
}

FRotator APacManCharacter::GetRotation(FVector Vector) {
	FRotator Rotation = FRotator(0, 0, 0);

	if (Vector.X > 0) {
		Rotation.Yaw = 0;
	}
	else if (Vector.X < 0) {
		{
			Rotation.Yaw = 180;
		}
	}

	if (Vector.Y > 0) {
		Rotation.Yaw = 90;
	}
	else if (Vector.Y < 0) {
		{
			Rotation.Yaw = 270;
		}
	}

	return Rotation;
}

void APacManCharacter::MoveYAxis(float AxisValue)
{
	if (AxisValue) {
		CurrentVelocity.Y = AxisValue;
		AddMovementInput(CurrentVelocity);

		FRotator Rotation = GetRotation(CurrentVelocity);
		SetActorRotation(Rotation);
	}
	else
		CurrentVelocity.Y = 0;
}

void APacManCharacter::Kill()
{
	if (--Lives == 0) {
		m_GameMode->SetCurrentState(EGameState::EGameOver);
	} else {
		SetActorLocation(m_StartPoint);
	}
}