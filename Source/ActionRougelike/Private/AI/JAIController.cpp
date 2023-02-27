// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/JAIController.h"
#include "AI/JAICharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AJAIController::AJAIController()
{
	//
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComp");
}

void AJAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	AJAICharacter* AICharacter = Cast<AJAICharacter>(InPawn);

	//运行行为树
	BehaviorTreeComp->StartTree(*BehaviorTree);

	//设置黑板资源
	AICharacter->BlackboardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);

}

void AJAIController::OnUnPossess()
{
	Super::OnUnPossess();
	//停止行为树
	BehaviorTreeComp->StopTree(EBTStopMode::Safe);

}
