// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ActionRougelikeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API AActionRougelikeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	/** 移除当前菜单控件，并在指定类（如有）中新建控件。*/
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	/** 游戏开始时调用。*/
	virtual void BeginPlay() override;

	/** 游戏开始时，用作菜单的控件类。*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	/** 用作菜单的控件实例。*/
	UPROPERTY()
		UUserWidget* CurrentWidget;
};
