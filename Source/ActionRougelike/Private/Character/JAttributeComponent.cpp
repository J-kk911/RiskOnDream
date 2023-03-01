// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/JAttributeComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UJAttributeComponent::UJAttributeComponent()
{
	Health = 100.0f;
}


bool UJAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool UJAttributeComponent::ApplyHealthChange(float Delta,FVector Location,AActor* Instigator)
{
	if (Instigator) {
		UE_LOG(LogTemp, Warning, TEXT("attributeComp"));
	}
	if (Health <= 0) return false;
	//UE_LOG(LogTemp, Warning, TEXT("ATTACK!!"))
	FString Deamge = FString::SanitizeFloat(Delta);
	DrawDebugString(GetWorld(),Location, Deamge, NULL, FColor::Red, 0.5, false, 1.f);
	Health += Delta;
	OnHealthChanged.Broadcast(Instigator,this,Health,Delta);
	return true;
}

float UJAttributeComponent::GetHealth()
{
	return this->Health;
}

void UJAttributeComponent::SetHealth(float MaxHealth)
{
	Health = MaxHealth;
}

