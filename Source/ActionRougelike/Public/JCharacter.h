// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "JCharacter.generated.h"



UCLASS()
class ACTIONROUGELIKE_API AJCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	//在蓝图中手动设置一个类的实例
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

public:
	// Sets default values for this character's properties
	AJCharacter();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//摄像机械臂
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	//摄像头
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	//向前移动
	void MoveForward(float value);
	//向右移动
	void MoveRight(float value);
	//初级攻击
	void PrimaryAttack();

	//控制视野转动handle
	FTimerHandle ViewModDelay;

	//恢复正常视野
	void RotationToMovement();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
