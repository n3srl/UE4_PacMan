// Fill out your copyright notice in the Description page of Project Settings.
#include "Enemy.h"
#include "AIEnemy.h"

void AAIEnemy::OnPossess(class APawn* InPawn)
{
	Super::OnPossess(InPawn);
	m_Bot = Cast<AEnemy>(InPawn);

	m_HomeLocation = m_Bot->GetActorLocation();
	SearchNewPoint();
}
// simple return to the home location and start a timer for the deadh
void AAIEnemy::GoHome()
{
	MoveToLocation(m_HomeLocation);
	GetWorldTimerManager().SetTimer(m_TimerDead, this,
		&AAIEnemy::Rearm, 5.0f, false);
}
// call the timer and return to walk
void AAIEnemy::Rearm()
{
	GetWorldTimerManager().ClearTimer(m_TimerDead);
	m_Bot->Rearm();
}
// when the pawn ends a move, return to move if is not dead

void AAIEnemy::OnMoveCompleted(FAIRequestID RequestID,
	EPathFollowingResult::Type Result)
{
	if (!m_Bot->bIsDead) { SearchNewPoint(); }
}
// stop the pawn movements
void AAIEnemy::StopMove()
{
	StopMovement();

}

// in order to find a new point we search if there is a navigation mesh activeand
// when found, we simple call the GetRandomPointInRadius function from the NavMesh
void AAIEnemy::SearchNewPoint()
{
/*	
	UNavigationSystemV1* NavMesh =FNavigationSystem::GetCurrent< UNavigationSystemV1>(Cast<UObject>(this));

	if (NavMesh)
	{
		const float SearchRadius = 10000.0f;
		FNavLocation RandomPt;
		//				       GetRandomReachablePointInRadius(UObject* WorldContextObject, const FVector& Origin, float Radius, ANavigationData* NavData, TSubclassOf<UNavigationQueryFilter> FilterClass)
		bool bFound = NavMesh->GetRandomReachablePointInRadius(m_Bot->GetActorLocation(), SearchRadius, RandomPt);
		if (bFound)
		{
			MoveToLocation(RandomPt.Location);
		}
	}
	*/
}