// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "JCrossHairHUD.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API AJCrossHairHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AJCrossHairHUD();


	//virtual void DrawHUD() override;

protected:
UPROPERTY(EditAnywhere)
	UTexture2D* CrosshairTex;;
};
