// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JInteractionComponent.h"
#include "GameFramework/Character.h"
#include "JCharacter.generated.h"

class JAttributeComponent;
class UCameraComponent;
class USpringArmComponent;
class UAnimMontage;

UCLASS()
class ACTIONROUGELIKE_API AJCharacter : public ACharacter
{
	GENERATED_BODY()

//攻击相关
private:
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

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* DeadthAnim;

	//抬手延迟
	UPROPERTY(EditAnywhere, Category = "Attack")
	float TimeToHandUp = 0.2;

//其他私有变量
private:
	//控制视野转动handle
	FTimerHandle ViewModDelay;

	//攻击延迟
	FTimerHandle AttackDelay;

	UPROPERTY(EditAnywhere)
	FTimerHandle RestartLevelTimeHandle;

	UPROPERTY(EditAnywhere)
	float TimeToRestart = 3.0f;

//人物控制函数
private:
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
	//退出游戏
	void QuitGame();
	//重新开始当前关卡
	void ReatartLevel();

//私有函数
private:
	UFUNCTION(BlueprintCallable)
		void OnHealthChanged(AActor* InstigatorActor, UJAttributeComponent* OwningComp, float NewHealth, float Delta);

//重写函数
public:
	// Sets default values for this character's properties
	AJCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

//需要调用的组件
public:
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



};
