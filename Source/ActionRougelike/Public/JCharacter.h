// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UJInteractionComponent;
class UAnimMontage;

UCLASS()
class ACTIONROUGELIKE_API AJCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	//在蓝图中手动设置一个类的实例，子弹
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	//播放动画
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	//抬手延迟
	UPROPERTY(EditAnywhere, Category = "Attack")
	float TimeToHandUp = 0.2;

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

	//控制视野转动handle
	FTimerHandle ViewModDelay;

	//攻击延迟
	FTimerHandle AttackDelay;

	//actor组件
	UJInteractionComponent* InteractionComp;


	 
	//向前移动
	void MoveForward(float value);
	//向右移动
	void MoveRight(float value);
	//初级攻击
	void PrimaryAttack();
	//抬手延迟
	void PrimaryAttackDelay();
	//恢复正常视野
	void RotationToMovement();
	//交互
	void PrimaryInteract();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
