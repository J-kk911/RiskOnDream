// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "JBaseProjectile.generated.h"

UCLASS()
class ACTIONROUGELIKE_API AJBaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJBaseProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//球体组件
	UPROPERTY(VisibleAnywhere)
		USphereComponent* SphereComp;
	//移动组件
	UPROPERTY(VisibleAnywhere)
		UProjectileMovementComponent* MovementComp;
	//生成粒子特效
	UPROPERTY(VisibleAnywhere, Category = "Particle")
		UParticleSystemComponent* ParticleStartComp;
	//飞行粒子特效
	UPROPERTY(VisibleAnywhere, Category = "Particle")
		UParticleSystemComponent* ParticleFlyComp;
	//结束粒子特效
	UPROPERTY(VisibleAnywhere, Category = "Particle")
		UParticleSystemComponent* ParticleEndComp;
	//生成音效
	UPROPERTY(VisibleAnywhere, Category = "Audio")
		UAudioComponent* AudioStartComp;
	//飞行音效
	UPROPERTY(VisibleAnywhere, Category = "Audio")
		UAudioComponent* AudioFlyComp;
	//结束音效
	UPROPERTY(VisibleAnywhere, Category = "Audio")
		UAudioComponent* AudioEndComp;
	
	//撞击后
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void Destroy();
protected:
	UPROPERTY(VisibleAnywhere)
		float TimeToDestroy = 0.5;
	UPROPERTY(VisibleAnywhere)
		FTimerHandle DestroyTimeHandle;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
