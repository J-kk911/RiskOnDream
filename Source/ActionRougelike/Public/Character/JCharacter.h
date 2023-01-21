// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JInteractionComponent.h"
#include "JAttributeComponent.h"
#include "GameFramework/Character.h"
#include "JCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UAnimMontage;

UCLASS()
class ACTIONROUGELIKE_API AJCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	//在蓝图中手动设置一个类的实例，魔法子弹
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> MagiskProjectileClass;

	//在蓝图中手动设置一个类的实例，黑洞子弹
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> BlackholeProjectileClass;

	//在蓝图中手动设置一个类的实例，位移子弹
	UPROPERTY(EditAnywhere, Category = "Attack")
		TSubclassOf<AActor> DisplacementProjectileClass;

	//播放动画
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	//抬手延迟
	UPROPERTY(EditAnywhere, Category = "Attack")
	float TimeToHandUp = 0.2;

public:
	// Sets default values for this character's properties
	AJCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//摄像机械臂
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	//摄像头
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	//属性组件
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Component")
	UJAttributeComponent* AttributeComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	//互动接口组件
	UJInteractionComponent* InteractionComp;

	//控制视野转动handle
	FTimerHandle ViewModDelay;

	//攻击延迟
	FTimerHandle AttackDelay;



	//向前移动
	void MoveForward(float value);
	//向右移动
	void MoveRight(float value);
	//魔法攻击
	void MagiskProjectileAttack();
	//黑洞攻击
	void BlackholeProjectileAttack();
	//位移投射物
	void DisplacementProjectileAttack();
	//发射子弹
	void SendProjectile(TSubclassOf<AActor>);
	//由移动控制方向
	void RotationToMovement();
	//由视角控制方向
	void RotationToAttack();
	//交互
	void PrimaryInteract();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
