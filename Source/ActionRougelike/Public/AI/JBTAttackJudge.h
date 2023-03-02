// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "JBTAttackJudge.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API UJBTAttackJudge : public UBTDecorator
{
	GENERATED_BODY()
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere)
	float AttackDis = 500.0f;

};
