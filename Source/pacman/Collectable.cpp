// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable.h"

// Sets default values
ACollectable::ACollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetActorEnableCollision(true);
	BaseCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT ("BaseCollisionComponent"));

	CollectableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollectableMesh"));
	CollectableMesh->AttachTo(BaseCollisionComponent);

}


