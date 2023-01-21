// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JBaseProjectile.h"
#include "GameFramework/Actor.h"
#include "JDisplacementProjectile.generated.h"



UCLASS()
class ACTIONROUGELIKE_API AJDisplacementProjectile : public AJBaseProjectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJDisplacementProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ReadyToDestroy() override;

	

	UPROPERTY()
		float ExistTime = 0.5f;

	FTimerHandle ExistTimeHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
