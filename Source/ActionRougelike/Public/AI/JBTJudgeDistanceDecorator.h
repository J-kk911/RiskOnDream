// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "JBTJudgeDistanceDecorator.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API UJBTJudgeDistanceDecorator : public UBTDecorator
{
	GENERATED_BODY()
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, Category = LimitDis)
	float fDis = 100.0f;
};
