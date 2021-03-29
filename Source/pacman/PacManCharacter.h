#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "pacmanGameModeBase.h"
#include "Collectable.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/Classes/Components/CapsuleComponent.h"
#include "Engine/Classes/Components/PrimitiveComponent.h"
#include "Engine/Public/EngineUtils.h"
#include "Particles/ParticleSystemComponent.h"


#include "PacManCharacter.generated.h"

UCLASS()
class PACMAN_API APacManCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY()
	class UParticleSystemComponent* OurParticleSystem;

	FVector CurrentVelocity;

	// Sets default values for this character's properties
	APacManCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void Tick(float) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent*) override;

	UFUNCTION(BlueprintCallable, Category = "Pacman")
	void Kill();

	UFUNCTION(BlueprintCallable, Category = "Pacman")
	FString GetLives();

	UFUNCTION(BlueprintCallable, Category = "Pacman")
	void OnCollision(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pacman")
	int32 Lives; // player total lives

private:
	ApacmanGameModeBase* m_GameMode;


	FVector m_StartPoint; // the start point of the player
	void MoveXAxis(float);
	void MoveYAxis(float);
	// key events
	void NewGame();
	void Pause();
	void RestartGame();
	FRotator GetRotation(FVector);

							
};

