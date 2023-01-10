// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "JMagicProjectile.generated.h"

UCLASS()
class ACTIONROUGELIKE_API AJMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJMagicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//球体组件
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;

	//移动组件
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;

	//粒子特效组件
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
