// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/JBTAttackTaskNode.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AI/JAIController.h"
#include "AI/JAICharacter.h"

EBTNodeResult::Type UJBTAttackTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//通过行为树组件获得控制器
	AJAIController* AAIController = Cast<AJAIController>(OwnerComp.GetOwner());
	//通过控制器获得Character
	AJAICharacter* AAICharacter = Cast<AJAICharacter>(AAIController->GetPawn());

	AAICharacter->Attack();
	return EBTNodeResult::Succeeded;
}
