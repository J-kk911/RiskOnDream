// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/JInteractionComponent.h"
#include "JGamePlayInterface.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"



// Sets default values for this component's properties
UJInteractionComponent::UJInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}




// Called when the game starts
void UJInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UJInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UJInteractionComponent::PrimaryInteract()
{

	FHitResult OutHit;
	

	AActor* MyOwner = GetOwner();
	FRotator EyeRoation;
	//MyOwner->GetActorEyesViewPoint(EyeLocation,EyeRoation);

	FMinimalViewInfo OutResult;
	MyOwner->CalcCamera(GetWorld()->TimeSeconds,OutResult);

	FVector Start = OutResult.Location;;
	FRotator StartRotation = OutResult.Rotation;

	FVector End = Start + (StartRotation.Vector()*1500);

	FCollisionQueryParams Params;

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *Start.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *End.ToString());
	// 
	//射线检测： 检测结果，射线起点，射线终点，检测类型，忽略物体；
	bool bBlock =  GetWorld()->LineTraceSingleByObjectType(OutHit, Start, End,ECC_WorldDynamic, Params);
	
	AActor* HitActor = OutHit.GetActor();
	if (HitActor) {
		//如果这个目标继承自互动接口
		if (HitActor->Implements<UJGamePlayInterface>()) 
		{
			APawn* MyPawn = Cast<APawn>(MyOwner);
			IJGamePlayInterface::Execute_Interact(HitActor,MyPawn);
		}
	}

	//FColor LineColor;
	//if (bBlock) {
	//	LineColor = FColor::Green;
	//}
	//else {
	//	LineColor = FColor::Red;
	//}
	//DrawDebugLine(GetWorld(), Start, End, LineColor,false,2.0f,0,2.0f);
}