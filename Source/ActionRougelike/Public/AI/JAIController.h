// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "JAIController.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API AJAIController : public AAIController
{
	GENERATED_BODY()

public:
	AJAIController();

	virtual void OnPossess(APawn* InPawn)override;

	virtual void OnUnPossess()override;

public:

	//行为树组件
	UPROPERTY(EditAnywhere)
	class UBehaviorTreeComponent* BehaviorTreeComp;
	UPROPERTY(EditAnywhere)
	//行为树
	class UBehaviorTree* BehaviorTree;

public:
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorTreeComp();
};
