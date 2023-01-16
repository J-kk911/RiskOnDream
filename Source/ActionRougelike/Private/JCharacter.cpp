// Fill out your copyright notice in the Description page of Project Settings.


#include "JCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "JInteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "JMagicProjectile.h"


// Sets default values
AJCharacter::AJCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//赋予实例，并依附于根组件
	SpringArmComp = CreateDefaultSubobject <USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject <UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<UJInteractionComponent>("InteractionComp");
	
	//使用 Controller 控制摄像机臂旋转
	SpringArmComp->bUsePawnControlRotation = true;

	//角色朝向controller方向

	//不使用 Controller 控制角色旋转
	bUseControllerRotationYaw = false;
	
	//角色自动朝向运动方向
	GetCharacterMovement()->bOrientRotationToMovement = true;

	
}

// Called when the game starts or when spawned
void AJCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}





// Called every frame
void AJCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//UE_LOG(LogTemp, Error, TEXT("%d"), bUseControllerRotationYaw ? 1 : 0);

}

// Called to bind functionality to input
void AJCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//移动
	PlayerInputComponent->BindAxis("MoveForward",this,&AJCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AJCharacter::MoveRight);


	//视角，将动作输入到 Controller
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	//操作
	PlayerInputComponent->BindAction("PrimaryAttack",IE_Pressed,this,&AJCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AJCharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AJCharacter::PrimaryInteract);
}


void AJCharacter::MoveForward(float value)
{

	//获得相机的Rotation方向
	FRotator ControlRot = GetControlRotation();
	//转换为相机的前进方向
	FVector ContorlFrontVector = UKismetMathLibrary::GetForwardVector(ControlRot);
	//输入到input
	AddMovementInput(ContorlFrontVector, value);
}

void AJCharacter::MoveRight(float value)
{

	//获得相机的Rotation方向
	FRotator ControlRot = GetControlRotation();
	//转换为相机的前进方向
	FVector ContorlRightVector = UKismetMathLibrary::GetRightVector(ControlRot);
	//输入到Movementinput
	AddMovementInput(ContorlRightVector,value);
}




void AJCharacter::PrimaryAttack()
{
	//一旦攻击，角色就朝向攻击方向，并延迟1.0f秒
	GetWorldTimerManager().SetTimer(ViewModDelay,this,&AJCharacter::RotationToMovement,1.0f);
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = true;
	//SetActorRotation()加上延迟

	PlayAnimMontage(AttackAnim);
	//延迟播放动画
	GetWorldTimerManager().SetTimer(AttackDelay, this, &AJCharacter::PrimaryAttackDelay, TimeToHandUp);

}
void AJCharacter::PrimaryAttackDelay(){
	//设置在手上发射
	FVector HandLocation = GetMesh()->GetSocketLocation("ik_hand_r");

	//射线检测
	FHitResult OutHit;
	FVector Start = CameraComp->GetComponentLocation();
	FRotator StartRotation = CameraComp->GetComponentRotation();
	FVector End = Start + (StartRotation.Vector() * 100000);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *Start.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *End.ToString());
	// 
	//射线检测： 检测结果，射线起点，射线终点，射线类型，忽略物体；
	bool bBlock = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_WorldDynamic, Params);

	FRotator TargetRotation;
	if (bBlock) {
		TargetRotation = UKismetMathLibrary::FindLookAtRotation(HandLocation, OutHit.Location);
		//UE_LOG(LogTemp, Warning, TEXT("FIND:%s"), *OutHit.Location.ToString());
	}else{
		TargetRotation = UKismetMathLibrary::FindLookAtRotation(HandLocation, End);
		//UE_LOG(LogTemp, Warning, TEXT("NOT FIND:%s"), *End.ToString());
		
	}

	FTransform SpawnTM = FTransform(TargetRotation, HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

void AJCharacter::RotationToMovement() {
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	GetWorldTimerManager().ClearTimer(ViewModDelay);
}

void AJCharacter::PrimaryInteract()
{
	InteractionComp->PrimaryInteract();
}