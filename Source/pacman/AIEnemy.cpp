	// Fill out your copyright notice in the Description page of Project Settings.
#include "Enemy.h"
#include "AIEnemy.h"

void AAIEnemy::OnPossess(class APawn* InPawn)
{
	Super::OnPossess(InPawn);
	m_Bot = Cast<AEnemy>(InPawn);
	m_Actor = InPawn;

	UE_LOG(LogTemp, Warning, TEXT("IA POSSESSED ENEMY"));

	if (m_Bot == nullptr) {
		m_HomeLocation = m_Actor->GetActorLocation();
		UE_LOG(LogTemp, Warning, TEXT("Not a AEnemy"));

	}
	else {
		m_HomeLocation = m_Bot->GetActorLocation();
	}
	
	SearchNewPoint();
}

// simple return to the home location and start a timer for the deadh
void AAIEnemy::GoHome()
{
	UE_LOG(LogTemp, Warning, TEXT("IA GoHome"));
	MoveToLocation(m_HomeLocation);
	GetWorldTimerManager().SetTimer(m_TimerDead, this,
		&AAIEnemy::Rearm, 5.0f, false);
}

// call the timer and return to walk
void AAIEnemy::Rearm()
{
	UE_LOG(LogTemp, Warning, TEXT("IA Rearm"));
	GetWorldTimerManager().ClearTimer(m_TimerDead);
	m_Bot->Rearm();
}

// when the pawn ends a move, return to move if is not dead
void AAIEnemy::OnMoveCompleted(FAIRequestID RequestID,
	EPathFollowingResult::Type Result)
{
	UE_LOG(LogTemp, Warning, TEXT("IA OnMoveCompleted"));
	if (!m_Bot->bIsDead) { SearchNewPoint(); }
}
// stop the pawn movements
void AAIEnemy::StopMove()
{
	UE_LOG(LogTemp, Warning, TEXT("IA StopMove"));
	StopMovement();

}

// in order to find a new point we search if there is a navigation mesh activeand
// when found, we simple call the GetRandomPointInRadius function from the NavMesh
void AAIEnemy::SearchNewPoint()
{
	const UNavigationSystemV1* NavMesh = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	
	if (NavMesh)
	{
		
		UObject* WorldContextObject = GetWorld(); //UObject* WorldContextObject
		FVector origin = m_Actor->GetActorLocation(); //const FVector& Origin
		float SearchRadius = -1.0f; //float Radius
		ANavigationData* NavData = Cast< ANavigationData>(NavMesh->GetNavDataForActor(*m_Actor)); //ANavigationData* NavData
		TSubclassOf<UNavigationQueryFilter> FilterClass = UNavigationQueryFilter::StaticClass();//TSubclassOf<UNavigationQueryFilter>
		FVector RandomPt;

		RandomPt = NavMesh->GetRandomPointInNavigableRadius( WorldContextObject, origin, SearchRadius, NavData, FilterClass);

		if (RandomPt == m_PreviousRandomPoint) { //FIX stack overflow
			UE_LOG(LogTemp, Error, TEXT("IA SearchNewPoint FAILED %f,%f,%f"), RandomPt.X, RandomPt.Y, RandomPt.Z);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("IA SearchNewPoint %f,%f,%f"), RandomPt.X, RandomPt.Y, RandomPt.Z);
				(RandomPt);
		}

		m_PreviousRandomPoint = RandomPt;
	}
}