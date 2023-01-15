// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JGamePlayInterface.h"
#include "Components/TimelineComponent.h"
#include "JItemChest.generated.h"



UCLASS()
class ACTIONROUGELIKE_API AJItemChest : public AActor, public IJGamePlayInterface
{
	GENERATED_BODY()
	//实现接口
	void Interact_Implementation(APawn* OperaterPawn) override;

public:	
	// Sets default values for this actor's properties
	AJItemChest();

	UPROPERTY(EditDefaultsOnly)
	UTimelineComponent* OpenTimeline;

	// 声明曲线对象,要在蓝图里
	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* Curver;

public:
	UFUNCTION()
		void OnTimelineTick(float Output);	// Timeline 更新时调用

	UFUNCTION()
		void SetState();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh;

	UPROPERTY(EditDefaultsOnly)
	bool Open = false;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	

};
