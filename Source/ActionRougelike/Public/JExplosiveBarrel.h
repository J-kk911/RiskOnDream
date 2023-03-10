// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <PhysicsEngine/RadialForceComponent.h>
#include "JExplosiveBarrel.generated.h"

UCLASS()
class ACTIONROUGELIKE_API AJExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJExplosiveBarrel();

protected:

	//Mesh 组件
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	//冲击波 组件
	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForceComp;

	//例子特效
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;

	//音效
	UPROPERTY(VisibleAnywhere)
	UAudioComponent* AudioComp;

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	float ImpulseRadius = 750.0f;
	
	bool Hited = false;
};
