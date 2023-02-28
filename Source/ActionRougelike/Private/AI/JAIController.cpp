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
	RootComponent->Activate(true);
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComp");

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeAssert(TEXT("/Game/RiskOnDream/AI/BehaviorTree")); // 找到编辑器中的行为树
	if (BehaviorTreeAssert.Succeeded())
	{
		BehaviorTree = BehaviorTreeAssert.Object; // 分配给tree
	}

}

void AJAIController::OnPossess(APawn* InPawn)
{


	AJAICharacter* AICharacter = Cast<AJAICharacter>(InPawn);
	if (AICharacter == nullptr) {
		return;
	}

	Super::OnPossess(InPawn);

	if (BehaviorTreeComp != nullptr)
	{
		if (BehaviorTree != nullptr) {
			//运行行为树
			BehaviorTreeComp->StartTree(*BehaviorTree);
			AICharacter->BlackboardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset); // 初始化
			UE_LOG(LogTemp, Error, TEXT("start"));
		}
	}
}

void AJAIController::OnUnPossess()
{
	Super::OnUnPossess();
	//停止行为树
	BehaviorTreeComp->StopTree(EBTStopMode::Safe);


}



FORCEINLINE UBehaviorTreeComponent* AJAIController::GetBehaviorTreeComp()
{
	return AJAIController::BehaviorTreeComp;
}
