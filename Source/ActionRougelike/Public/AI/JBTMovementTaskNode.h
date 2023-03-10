// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "JBTMovementTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API UJBTMovementTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
	//重载执行任务函数
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
