// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "JBaseProjectile.h"
#include "JMagicProjectile.generated.h"

UCLASS()
class ACTIONROUGELIKE_API AJMagicProjectile : public AJBaseProjectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJMagicProjectile();

protected:
	UFUNCTION()
	void OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool Hit = false;

	
};
