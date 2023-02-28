// Fill out your copyright notice in the Description page of Project Settings.
// ÅÐ¶ÏÊÇ·ñ¾àÀë¹ý½ü
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "JBTDecorator.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API UJBTDecorator : public UBTDecorator
{
	GENERATED_BODY()
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere,Category = LimitDis)
	float fDis = 100.0f;
};
