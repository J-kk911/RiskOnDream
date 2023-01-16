// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
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
	
	//等待销毁时间
	UPROPERTY(VisibleAnywhere)
	float WaitTime = 0.5; 

	//延迟销毁
	FTimerHandle TimeToDestroy;

	//声音特效
	UPROPERTY(VisibleAnywhere)
	UAudioComponent* AudioComp;


	//被打击
	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//销毁
	void Destroy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
