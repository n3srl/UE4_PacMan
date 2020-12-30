// Fill out your copyright notice in the Description page of Project Settings.
#include "PacManCharacter.h"

// Sets default values
APacManCharacter::APacManCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetActorEnableCollision(true);
}

// Called when the game starts or when spawned
void APacManCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_GameMode = Cast<ApacmanGameModeBase>(UGameplayStatics::GetGameMode(this));
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APacManCharacter::OnCollision);

	// find out how many collectables the player need to eat in order to win
	for (TActorIterator<ACollectable> CollectableItr(GetWorld()); CollectableItr; ++CollectableItr)
	{
		m_CollectablesToEat++;
	}

	m_StartPoint = GetActorLocation(); // simple get the player location
	m_Lives = 3; // set the full life when start
}

void APacManCharacter::OnCollision(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// enter on deeper check only if playing
	if ( m_GameMode->GetCurrentState() == EGameState::EPlaying ) {

		// check if is a true collectable
		if ( OtherActor->IsA( ACollectable::StaticClass() ) )
		{
			// in any case, destroy that collectable!
			OtherActor->Destroy();
		}

		if ( --m_CollectablesToEat == 0 ) {
			m_GameMode->SetCurrentState(EGameState::EWin);
		}

	}
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
	CurrentVelocity.X = AxisValue;
	AddMovementInput(CurrentVelocity);
}

void APacManCharacter::MoveYAxis(float AxisValue)
{
	CurrentVelocity.Y = AxisValue;
	AddMovementInput(CurrentVelocity);
}

void APacManCharacter::Kill()
{
	if (--m_Lives == 0) {
		m_GameMode->SetCurrentState(EGameState::EGameOver);
	} else {
		SetActorLocation(m_StartPoint);
	}
}