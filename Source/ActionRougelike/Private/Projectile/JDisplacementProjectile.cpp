// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/JDisplacementProjectile.h"

// Sets default values
AJDisplacementProjectile::AJDisplacementProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MovementComp->InitialSpeed = 3000.0f;

}

// Called when the game starts or when spawned
void AJDisplacementProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(DestroyTimeHandle, this, &AJDisplacementProjectile::ReadyToDestroy, ExistTime);
}


// Called every frame
void AJDisplacementProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJDisplacementProjectile::ReadyToDestroy()
{
	Super::ReadyToDestroy();
	GetInstigator()->SetActorLocation(GetActorLocation());

}

