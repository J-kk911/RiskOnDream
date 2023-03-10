// Fill out your copyright notice in the Description page of Project Settings.
// 最好不要在这里更新黑板的值

#include "AI/JAICharacter.h"
#include "AI/JAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/JAttributeComponent.h"
#include "Character/JCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AJAICharacter::AJAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//设置AI控制类
	AIControllerClass = AJAIController::StaticClass();

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensing");
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComp");
	AttributeComp = CreateDefaultSubobject<UJAttributeComponent>("AttributeComp");


}

void AJAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//函数绑定到事件上，跟随事件触发
	AttributeComp->OnHealthChanged.AddDynamic(this, &AJAICharacter::OnHealthChanged);
}

// Called when the game starts or when spawned
void AJAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	AJAIController* AIController = Cast<AJAIController>(GetController());

	//绑定看到角色时候的动作
	PawnSensingComp->OnSeePawn.AddDynamic(AIController, &AJAIController::HaveSeePawn);

	AttributeComp->SetHealth(200.0);
	RLocation = GetActorLocation();
	LLocation = RLocation + GetActorRightVector()*3000;
	PatrolLocation = LLocation;
	GetWorldTimerManager().SetTimer(PatrolChangeTimeHandle, this, &AJAICharacter::ChangePatrolLocation, TimeToChangePatrol, true);
}

void AJAICharacter::ChangePatrolLocation()
{
	if (PatrolLocation == LLocation) {
		PatrolLocation = RLocation;
	}
	else {
		PatrolLocation = LLocation;
	}
}




// Called every frame
void AJAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("%f"),AttributeComp->GetHealth());
}

// Called to bind functionality to input
void AJAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



void AJAICharacter::OnHealthChanged(AActor* InstigatorActor, UJAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (NewHealth <= 0.0f) {
		PlayAnimMontage(DeadthAnim);
		AAIController* AIController = Cast<AAIController>(GetController());
		//AIControllerClass = NULL;//
		this->Controller->UnPossess();
	}



	//进入战斗状态
	if (Delta < 0) {
		if (InstigatorActor) {
			//UE_LOG(LogTemp, Warning, TEXT("character"));
			BlackboardComp->SetValueAsVector("TargetLocation", InstigatorActor->GetActorLocation());
		}
		ChangeToAttackMode();
	}


	//进入受击状态
	if (Delta < 0) 
	{
		BlackboardComp->SetValueAsBool("bPlayAttackedAnim", true);
	
		GetWorldTimerManager().SetTimer(RecoveryAttackedTimeHandle, this, &AJAICharacter::RecoveryAttackMode, 0.5f, false);
	}

}

void AJAICharacter::Attack()
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(AttackAnimTimeHandle, this, &AJAICharacter::DealDemage, TimeToDealDemage);
	AttackCDTimeHandle.Invalidate();
	GetWorldTimerManager().SetTimer(AttackCDTimeHandle, this, &AJAICharacter::AttackCDClaer, AttackCD);

}

void AJAICharacter::ChangeToAttackMode()
{
	UCharacterMovementComponent* MovementComp = Cast<UCharacterMovementComponent>(this->GetMovementComponent());
	MovementComp->MaxWalkSpeed = 1200.0f;

	GetWorldTimerManager().ClearTimer(AttackModeTimeHandle);
	GetWorldTimerManager().SetTimer(AttackModeTimeHandle, this, &AJAICharacter::RecoveryIdleMode, KeepAttackModeTime, false);
}

void AJAICharacter::RecoveryAttackMode()
{
	BlackboardComp->SetValueAsBool("bPlayAttackedAnim", false);
}

void AJAICharacter::DealDemage()
{
	TArray<struct FOverlapResult> OutOverlaps;
	const FVector Pos = GetActorLocation();
	FQuat Rot = GetActorQuat();
	ECollisionChannel TraceChannel = ECC_Pawn;
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(AttackRadius/2);
	CollisionShape.ShapeType = ECollisionShape::Sphere;
	GetWorld()->OverlapMultiByChannel(OutOverlaps, Pos, Rot, TraceChannel, CollisionShape);

	for (auto& OverLapPawn : OutOverlaps)
	{
		//如果存在组件则扣血
		UJAttributeComponent* OtherAttributeComp = Cast<UJAttributeComponent>(OverLapPawn.Actor->GetComponentByClass(UJAttributeComponent::StaticClass()));
		if (OtherAttributeComp && OtherAttributeComp->GetOwner()!=this) {
			OtherAttributeComp->ApplyHealthChange(-10.0, OverLapPawn.Actor->GetActorLocation(), this->GetInstigator());
		}
	}
}

void AJAICharacter::RecoveryIdleMode()
{
	UE_LOG(LogTemp, Warning, TEXT("recovery"));

	AttackModeTimeHandle.Invalidate();
}

void AJAICharacter::AttackCDClaer()
{
	AttackCDTimeHandle.Invalidate();
}
