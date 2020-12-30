// Copyright Epic Games, Inc. All Rights Reserved.

enum class EGameState : short
{
	EMenu,
	EPlaying,
	EPause,
	EWin,
	EGameOver
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/Public/EngineUtils.h"

#include "pacmanGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API ApacmanGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public :

	ApacmanGameModeBase();

	// getter of the game state
	EGameState GetCurrentState() const;

	// setter of the game state that handle further operations
	void SetCurrentState(EGameState value);

	void SetEnemyVulnerable();

	void BeginPlay() override;
private:
	EGameState m_CurrentState;
	
	TArray<class AEnemy*> m_Enemies;
	APlayerController* m_PlayerController;
};
