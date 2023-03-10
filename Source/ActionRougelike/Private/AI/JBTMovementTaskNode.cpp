// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/JBTMovementTaskNode.h"
#include "AI/JAIController.h"
#include "AI/JAICharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UJBTMovementTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//UE_LOG(LogTemp, Error, TEXT("go"));

	// 获得行为树的所属controler
	AJAIController* AIController = Cast<AJAIController>(OwnerComp.GetAIOwner());


	// 获得黑板上的数据
	AJAICharacter* AICharacter = Cast<AJAICharacter>(AIController->GetPawn());
	
	UBlackboardComponent* BlackboardComp = AICharacter->BlackboardComp;
	if (BlackboardComp != nullptr && AICharacter != nullptr) {
		FVector TargetLocation = BlackboardComp->GetValueAsVector(TEXT("TargetLocation"));

		AIController->MoveToLocation(TargetLocation);
		return EBTNodeResult::Succeeded;
		
		//UE_LOG(LogTemp, Error, TEXT("go! %s"), *TargetLocation.ToString());
		 // 让AI移动到targetlocation

	}
	return EBTNodeResult::Failed;
}
