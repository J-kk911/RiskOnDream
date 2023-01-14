// Fill out your copyright notice in the Description page of Project Settings.


#include "JItemChest.h"

// Sets default values
AJItemChest::AJItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitch = 110;
}

// Called when the game starts or when spawned
void AJItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJItemChest::Interact_Implementation(APawn* OperaterPawn)
{
	if (Open) {
		Open = false; 
		LidMesh->SetRelativeRotation(FRotator(0, 0, 0));
	}
	else {
		Open = true;
		LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
	}

}

