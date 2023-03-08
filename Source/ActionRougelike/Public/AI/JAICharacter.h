// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "JAICharacter.generated.h"

class JAttributeComponent;
class UJAttributeComponent;
class UBlackboardComponent;
UCLASS()
class ACTIONROUGELIKE_API AJAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	////当看到玩家
	//UFUNCTION()
	//void HaveSeePawn(APawn* Pawn);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//黑板组件资源
	UPROPERTY(EditAnywhere)
		UBlackboardComponent* BlackboardComp;

	//属性组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		UJAttributeComponent* AttributeComp;

	//视觉
	UPROPERTY(EditAnywhere, Category = See)
		UPawnSensingComponent* PawnSensingComp;

	//死亡动画
	UPROPERTY(EditAnywhere, Category = "Attack")
		UAnimMontage* DeadthAnim;

	UPROPERTY()
		AController* MyController;

	UFUNCTION()
		void OnHealthChanged(AActor* InstigatorActor, UJAttributeComponent* OwningComp, float NewHealth, float Delta);

	

//攻击
protected:
	UPROPERTY(EditAnywhere, Category = "Attack")
		float AttackCD = 5.0f;

	UPROPERTY(EditAnywhere,Category="Attack")
		float AttackRadius = 500.0f;

	UPROPERTY(EditAnyWhere, Category = "Attack")
		float TimeToDealDemage = 0.5f;

	UPROPERTY(EditAnyWhere, Category = "Attack")
		float Demage = 10.0f;

	UPROPERTY(EditAnyWhere, Category = "Attack")
		float IdleTime = 0.5f;


	UPROPERTY(EditAnywhere)
		UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere)
		UAnimMontage* AttackedAnim;

	UFUNCTION()
		void AttackCDClaer();

	UFUNCTION(BlueprintCallable)
		void DealDemage();

	UFUNCTION(BlueprintCallable)
		void AttackedLatelyClear();


public:

	UPROPERTY(VisibleAnywhere)
		FTimerHandle AttackTimeHandle;

	UPROPERTY()
		FTimerHandle AttackedLatelyTimeHandle;

	UPROPERTY()
		FTimerHandle AttackCDTimeHandle;

	UPROPERTY()
		FTimerHandle IdleTimeHandle;

	UFUNCTION()
		void Attack();
	
	//受击恢复
	UPROPERTY()
		FTimerHandle RecoveryAttackedTimeHandle;
	//受击恢复
	void RecoveryAttackedMode();
};
