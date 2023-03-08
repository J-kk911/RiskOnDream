// Fill out your copyright notice in the Description page of Project Settings.
// 用来驱动角色移动
// 最好在这里更新黑板值
// 

#include "Character/JCharacter.h"
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
	ControllPawn = InPawn;

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
			//UE_LOG(LogTemp, Error, TEXT("start"));
		}
	}
	AICharacter->BlackboardComp->SetValueAsVector("TargetLocation", AICharacter->GetActorLocation());

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

void AJAIController::HaveSeePawn(APawn* TargetPawn)
{
	//UE_LOG(LogTemp, Error, TEXT("this! "));

	TargetPawn = Cast<AJCharacter>(TargetPawn);
	if (TargetPawn) {
		FVector Location = TargetPawn->GetActorLocation();
		AJAICharacter* AICharacter  = Cast<AJAICharacter>(this->ControllPawn);
		//UE_LOG(LogTemp, Error, TEXT("i see you ! "));

		if (AICharacter) {
			AICharacter->BlackboardComp->SetValueAsVector("TargetLocation", Location);
			//UE_LOG(LogTemp, Error, TEXT("i see you %s "), *Location.ToString());
		}
	}
}