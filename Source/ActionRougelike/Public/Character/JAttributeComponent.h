// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JAttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROUGELIKE_API UJAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJAttributeComponent();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
		float Health;

public:
	UFUNCTION(BlueprintCallable, Category = "Attributes")

	bool ApplyHealthChange(float Delta);


	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetHealth();
		

};
