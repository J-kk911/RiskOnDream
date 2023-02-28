// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/JBTDecorator.h"
#include "AI/JAIController.h"
#include "AI/JAICharacter.h"
#include "Character/JCharacter.h"

bool UJBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UE_LOG(LogTemp, Error, TEXT("think "));

	AJAIController* AIC = Cast<AJAIController>(OwnerComp.GetAIOwner());
	if (AIC != nullptr)
	{
		AJAICharacter* AICharacter = Cast<AJAICharacter>(AIC->GetPawn());
		FVector AILocation = AICharacter->GetActorLocation();
		AJCharacter* Player = Cast<AJCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()); // 获得玩家
		if (Player != nullptr)
		{
			FVector PlayerLocation = Player->GetActorLocation();
			// 计算距离
			float Dis = (PlayerLocation - AILocation).Size();
			if (Dis < fDis)
			{
				return false; // 足够近，不移动了
			}
			else
			{
				return true; // 不够近，继续移动
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}