// Copyright Epic Games, Inc. All Rights Reserved.


#include "ActionRougelikeGameModeBase.h"

void AActionRougelikeGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
}

void AActionRougelikeGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
