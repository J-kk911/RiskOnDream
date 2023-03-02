// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "JAICharacter.generated.h"

class JAttributeComponent;
class UJAttributeComponent;
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


	//当看到玩家
	UFUNCTION()
	void HaveSeePawn(APawn* Pawn);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//黑板组件资源
	UPROPERTY(EditAnywhere)
	class UBlackboardComponent* BlackboardComp;

	//属性组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		UJAttributeComponent* AttributeComp;

	//视觉
	UPROPERTY(EditAnywhere, Category = See)
		UPawnSensingComponent* PawnSensingComp;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
		void OnHealthChanged(AActor* InstigatorActor, UJAttributeComponent* OwningComp, float NewHealth, float Delta);

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* DeadthAnim;

	UFUNCTION()
	void Attack();

	UPROPERTY(EditAnywhere)
	UAnimMontage* AttackAnim;

	UPROPERTY(VisibleAnywhere)
	FTimerHandle AttackTimeHandle;
	
	UPROPERTY(EditAnyWhere)
	float TimeToDealDemage = 0.5f; 

	UPROPERTY(EditAnyWhere)
	float Demage = 10.0f;

	UFUNCTION(BlueprintCallable)
	void DealDemage();

	UFUNCTION(BlueprintCallable)
	void AttackedLatelyClear();
	UPROPERTY()
	FTimerHandle AttackedLately;

public:
	UPROPERTY()
	FTimerHandle AttackCDTimeHandle;
	UFUNCTION()
	void AttackCDClaer();
	UPROPERTY(EditAnywhere)
	float AttackCD = 5.0f;

	UPROPERTY()
		float AttackRadius = 500.0f;

};
