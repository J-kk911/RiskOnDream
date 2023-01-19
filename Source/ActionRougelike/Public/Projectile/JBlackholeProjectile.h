// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JBaseProjectile.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "JBlackholeProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API AJBlackholeProjectile : public AJBaseProjectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AJBlackholeProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//³å»÷²¨×é¼þ
	UPROPERTY(VisibleAnywhere)
		URadialForceComponent* RadialForceComp;

	UPROPERTY()
	float ExistTime = 5.0f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
