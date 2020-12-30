// Copyright Epic Games, Inc. All Rights Reserved.


#include "pacmanGameModeBase.h"
#include "Enemy.h"


// in PacManGameMode.cpp
// there is no initializer by default, we need to add one
ApacmanGameModeBase::ApacmanGameModeBase()
{
	//search our custom pacman and set as default pawn if founded
	static ConstructorHelpers::FClassFinder<APawn>
		PlayerPawnOb(TEXT("Blueprint'/Game/Blueprints/BP_PacMan'"));

	if (PlayerPawnOb.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnOb.Class;
	}
}

void ApacmanGameModeBase::SetCurrentState(EGameState value)
{
	m_CurrentState = value;

	// for each enemy inside the level, use a switch case to the new state
		for (auto Iter(m_Enemies.CreateIterator()); Iter; Iter++) {
			switch (value)
			{
			case EGameState::EPlaying: // if start playing, initialize the enemies
				(*Iter)->SetMove(true);

				break;

			case EGameState::EGameOver:
				(*Iter)->Destroy();
				break;

				// same of gameover.
			case EGameState::EWin:
				(*Iter)->Destroy();
				break;

			case EGameState::EPause:

				(*Iter)->SetMove(false);
				break;

			default:
				// nothing
				break;
			}
		}
}

EGameState ApacmanGameModeBase::GetCurrentState() const
{
	return m_CurrentState;
}

// iterate all the enemies and make them vulnerable
void ApacmanGameModeBase::SetEnemyVulnerable()
{
	for (auto Iter(m_Enemies.CreateIterator()); Iter; Iter++) {
		(*Iter)->SetVulnerable();
	}
}

void ApacmanGameModeBase::BeginPlay() 
{
	Super::BeginPlay();

	// set to be on menu state as soon as the game start
	SetCurrentState(EGameState::EMenu);

	// find the first player controller and set it to our pc reference
	m_PlayerController = GetWorld()->GetFirstPlayerController();

	// find the ghosts in the scene and store them to our array
	for (TActorIterator<AEnemy> enemyIt(GetWorld()); enemyIt; ++enemyIt)
	{
		AEnemy* enemy = Cast< AEnemy >(*enemyIt);
		if (enemy) { m_Enemies.Add(enemy); }
	}
}