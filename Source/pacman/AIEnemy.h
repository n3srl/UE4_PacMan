class AEnemy;

#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "AI/NavigationSystemBase.h"
#include "NavigationSystem.h"

#include "pacmanGameModeBase.h"

#include "AIEnemy.generated.h"


/**
 * 
 */
UCLASS()
class PACMAN_API AAIEnemy : public AAIController
{
	GENERATED_BODY()

public:	
	void OnPossess(class APawn* InPawn) override;
	
	virtual void OnMoveCompleted(FAIRequestID RequestID,EPathFollowingResult::Type Result) override;
	
	UFUNCTION(BlueprintCallable, Category = "AIEnemy")
	void SearchNewPoint();
	UFUNCTION(BlueprintCallable, Category = "AIEnemy")
	void GoHome();
	UFUNCTION(BlueprintCallable, Category = "AIEnemy")
	void Rearm();
	UFUNCTION(BlueprintCallable, Category = "AIEnemy")
	void StopMove();

private:
	AEnemy* m_Bot;
	AActor* m_Actor;
	FVector m_HomeLocation;
	FTimerHandle m_TimerDead;
	FVector m_PreviousRandomPoint;
};
