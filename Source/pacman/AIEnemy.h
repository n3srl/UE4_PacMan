class AEnemy;

#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
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
	
	void SearchNewPoint();
	void GoHome();
	void Rearm();
	void StopMove();

private:
	AEnemy* m_Bot;
	FVector m_HomeLocation;
	FTimerHandle m_TimerDead;
};
