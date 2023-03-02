// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/JBTAttackJudge.h"
#include "AI/JAIController.h"
#include "AI/JAICharacter.h"

bool UJBTAttackJudge::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AJAIController* AIController = Cast<AJAIController>(OwnerComp.GetOwner());
	if (AIController != nullptr) {
		AJAICharacter* AICharacter = Cast<AJAICharacter>(AIController->GetPawn());

		FVector AILocation = AICharacter->GetActorLocation();
		FVector PLayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		if ((PLayerLocation - AILocation).Size() < AttackDis) {
			
			//确保攻击间隔，不能连续攻击
			if (!AICharacter->AttackCDTimeHandle.IsValid()) {
				return true;
			}
		}
	}
	
	return false;


}
