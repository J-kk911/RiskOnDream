// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/JBTJudgeDistanceDecorator.h"
#include "AI/JAIController.h"
#include "AI/JAICharacter.h"
#include "Character/JCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"



bool UJBTJudgeDistanceDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	//UE_LOG(LogTemp, Error, TEXT("think "));

	AJAIController* AIController = Cast<AJAIController>(OwnerComp.GetAIOwner());
	if (AIController != nullptr)
	{
		AJAICharacter* AICharacter = Cast<AJAICharacter>(AIController->GetPawn());
		FVector AILocation = AICharacter->GetActorLocation();
		UBlackboardComponent* BlackboardComp = AICharacter->BlackboardComp;
		FVector TargetLocation = BlackboardComp->GetValueAsVector(TEXT("TargetLocation"));
		// 计算距离
		float Dis = (TargetLocation - AILocation).Size();
		if (Dis > fDis)
		{
			return true; // 不够近，继续移动
		}
			
		
	}
	return false;
}
