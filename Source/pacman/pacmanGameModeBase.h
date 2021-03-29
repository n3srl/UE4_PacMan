#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/Public/EngineUtils.h"

#include "pacmanGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSetEnemyInvulnerableDelegate);

UENUM(BlueprintType)
enum class EGameState: uint8
{
	EMenu,
	EPlaying,
	EPause,
	EWin,
	EGameOver
};

/**
 * 
 */
UCLASS(Blueprintable)
class PACMAN_API ApacmanGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public :

	ApacmanGameModeBase();

	// getter of the game state
	EGameState GetCurrentState() const;

	// setter of the game state that handle further operations
	UFUNCTION(BlueprintCallable, Category = "PacmanGameMode")
		void SetCurrentState(EGameState value);
	// setter of the game state that handle further operations
	UFUNCTION(BlueprintCallable, Category = "PacmanGameMode")
		EGameState GetCurrentState();

	UFUNCTION(BlueprintCallable, Category = "PacmanGameMode")
	void SetEnemyVulnerable();

	UFUNCTION(BlueprintCallable, Category = "PacmanGameMode")
	void SetEnemyInvulnerable();

	void BeginPlay() override;

	void EatCollectible();

	UFUNCTION(BlueprintCallable, Category = "PacmanGameMode")
	int GetCollectablesEaten();

	UFUNCTION(BlueprintCallable, Category = "PacmanGameMode")
	void SetCollectablesToEat(int CollectablesToEat);

	UFUNCTION(BlueprintCallable, Category = "PacmanGameMode")
	bool IsPlayerWinning();


	UFUNCTION(BlueprintCallable, Category = "PacmanGameMode")
	bool IsEnemyVulnerable();

	UPROPERTY(EditAnywhere, Category = Body)
	float TimeEnemyVulnerable =10.0f;

	UPROPERTY(BlueprintAssignable,  Category = "PacmanGameMode")
	FSetEnemyInvulnerableDelegate OnUpdateInvulnerable;

private:
	EGameState m_CurrentState;
	
	TArray<class AEnemy*> m_Enemies;
	APlayerController* m_PlayerController;

	int m_CollectablesToEat = 0;
	int m_CollectablesCounter = 0;
	bool m_IsEnemyVulnerable=false;
	FTimerHandle m_TimerVulnerable;
};