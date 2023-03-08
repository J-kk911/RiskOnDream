// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JAttributeComponent.generated.h"

/*
* 多播的意思是可以绑定多个
自定义动态多播代理
	广播后，用来让上层函数触发
	定义了一种变量为FOnHealthChanged的变量
	在该文件的.cpp中可以用.broadcast()函数广播
 例：
	OnHealthChanged.Broadcast(Instigator, this, Health, Delta);
 
	上层通过将函数动态绑定到这个变量来实现调用
 例：
	AttributeComp->OnHealthChanged.AddDynamic(this, &AJAICharacter::OnHealthChanged);
*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, UJAttributeComponent*, OwningComp, float, NewHealth, float, Delta);

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
	//const 事件在蓝图里就不需要白条了
	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UPROPERTY(BlueprintAssignable)
		FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(float Delta,FVector Location,AActor* Instigator);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetHealth();
		
	void SetHealth(float MaxHealth);


};
