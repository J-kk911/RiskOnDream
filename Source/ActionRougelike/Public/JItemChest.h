// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JGamePlayInterface.h"
#include "JItemChest.generated.h"

UCLASS()
class ACTIONROUGELIKE_API AJItemChest : public AActor, public IJGamePlayInterface
{
	GENERATED_BODY()
	//实现接口
	void Interact_Implementation(APawn* OperaterPawn) override;

public:	
	// Sets default values for this actor's properties
	AJItemChest();

	UPROPERTY(EditAnywhere)
	float TargetPitch;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	

};
