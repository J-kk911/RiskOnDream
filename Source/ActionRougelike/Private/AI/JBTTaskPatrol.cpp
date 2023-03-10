// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/JBTTaskPatrol.h"
#include "AI/JAIController.h"
#include "AI/JAICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"



EBTNodeResult::Type UJBTTaskPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AJAIController* AIController = Cast<AJAIController>(OwnerComp.GetOwner());
	AJAICharacter* AICharacter = Cast<AJAICharacter>(AIController->GetPawn());
	UCharacterMovementComponent* MovementComp = Cast<UCharacterMovementComponent>(AICharacter->GetMovementComponent());
	if(AICharacter->AttackModeTimeHandle.IsValid())return EBTNodeResult::Failed;
	MovementComp->MaxWalkSpeed = 300.0f;
	AIController->MoveToLocation(AICharacter->PatrolLocation);
	return EBTNodeResult::Succeeded;
}
