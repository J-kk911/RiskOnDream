// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "JGamePlayInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UJGamePlayInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ACTIONROUGELIKE_API IJGamePlayInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//»¥¶¯½Ó¿Ú
	UFUNCTION(BlueprintNativeEvent)
	void Interact(APawn* OperaterPawn);


};
