// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/JAICharacter.h"
#include "AI/JAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/JAttributeComponent.h"

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
	
	//绑定看到角色时候的动作
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AJAICharacter::HaveSeePawn);

	BlackboardComp->SetValueAsVector("TargetLocation", this->GetActorLocation());

}


// Called every frame
void AJAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AJAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AJAICharacter::HaveSeePawn(APawn* Pawn)
{
	if (GetWorld()->GetFirstPlayerController()->GetPawn() == Pawn) {
		FVector Location = Pawn->GetActorLocation();
		BlackboardComp->SetValueAsVector("TargetLocation", Location);
		//UE_LOG(LogTemp, Error, TEXT("i see you %s "), *Location.ToString());
	}
}

void AJAICharacter::OnHealthChanged(AActor* InstigatorActor, UJAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (NewHealth <= 0.0f) {
		//UE_LOG(LogTemp, Warning, TEXT("xxx"))
		PlayAnimMontage(DeadthAnim);
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}


