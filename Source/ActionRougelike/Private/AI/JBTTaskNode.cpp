// Fill out your copyright notice in the Description page of Project Settings.
// 读取blackboard上的数据，用ai controller 控制角色移动

#include "AI/JBTTaskNode.h"
#include "AI/JAIController.h"
#include "AI/JAICharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UJBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Error, TEXT("go"));

	// 获得行为树的所属controler
	AJAIController* AIController = Cast<AJAIController>(OwnerComp.GetAIOwner());

	//FVector temp = { 0,0,0 };
	//AIController->MoveToLocation(temp);
	
	// 获得黑板上的数据
	AJAICharacter* AICharacter = Cast<AJAICharacter>(AIController->GetPawn());
	UBlackboardComponent* BlackboardComp = AICharacter->BlackboardComp;
	if (BlackboardComp != nullptr) {
		FVector TargetLocation = BlackboardComp->GetValueAsVector(TEXT("TargetLocation"));
		UE_LOG(LogTemp, Error, TEXT("go! %s"),*TargetLocation.ToString());
		if (AICharacter != nullptr) // 让AI移动到targetlocation
		{
			AIController->MoveToLocation(TargetLocation);
			return EBTNodeResult::Succeeded;
		}
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}
