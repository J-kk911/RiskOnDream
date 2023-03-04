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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* LidMesh;

	//设置一个时间线事件组件，用于在激活的时候，不断触发事件
	UPROPERTY(EditDefaultsOnly)
		UTimelineComponent* OpenTimeline;

	// 声明曲线对象,要在蓝图里
	UPROPERTY(EditDefaultsOnly)
		UCurveFloat* Curver;

	UPROPERTY(EditDefaultsOnly)
		bool Open = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnTimelineTick(float OpenAngle);	// Timeline 更新时调用

};
