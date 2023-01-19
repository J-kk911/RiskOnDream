// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/JCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectile/JMagicProjectile.h"


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
	
	AttributeComp = CreateDefaultSubobject<UJAttributeComponent>("AttributeComp");

	/*
	* 使用 Controller 控制摄像机臂旋转
	* 不使用 Controller 控制角色旋转
	* 角色自动朝向运动方向
	*/
	SpringArmComp->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;
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

	UE_LOG(LogTemp, Error, TEXT("%f"), AttributeComp->Health);

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
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AJCharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AJCharacter::PrimaryInteract);

	//攻击
	PlayerInputComponent->BindAction("MagiskProjectil", IE_Pressed, this, &AJCharacter::MagiskProjectileAttack);
	PlayerInputComponent->BindAction("BlackholeProjectile", IE_Pressed, this, &AJCharacter::BlackholeProjectileAttack);
	PlayerInputComponent->BindAction("DisplacementProjectile", IE_Pressed, this, &AJCharacter::DisplacementProjectileAttack);
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




void AJCharacter::MagiskProjectileAttack()
{
	RotationToAttack();

	PlayAnimMontage(AttackAnim);
	FTimerDelegate TimerDel;
	TimerDel.BindUObject(this, &AJCharacter::SendProjectile, MagiskProjectileClass);

	//子弹等待动画
	GetWorldTimerManager().SetTimer(AttackDelay, TimerDel, TimeToHandUp,false);

}

void AJCharacter::BlackholeProjectileAttack()
{
	RotationToAttack();

	PlayAnimMontage(AttackAnim);
	FTimerDelegate TimerDel;
	TimerDel.BindUObject(this, &AJCharacter::SendProjectile, BlackholeProjectileClass);

	//子弹等待动画
	GetWorldTimerManager().SetTimer(AttackDelay, TimerDel, TimeToHandUp, false);

}

void AJCharacter::DisplacementProjectileAttack()
{
	RotationToAttack();

	PlayAnimMontage(AttackAnim);
	FTimerDelegate TimerDel;
	TimerDel.BindUObject(this, &AJCharacter::SendProjectile, DisplacementProjectileClass);

	//子弹等待动画
	GetWorldTimerManager().SetTimer(AttackDelay, TimerDel, TimeToHandUp, false);

}

void AJCharacter::SendProjectile(TSubclassOf<AActor> ProjectileClass){

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
	HandLocation = HandLocation + TargetRotation.Vector() * 30;

	FTransform SpawnTM = FTransform(TargetRotation, HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	AActor* SpawnActor =  GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);

	Super::MoveIgnoreActorAdd(SpawnActor);

}

void AJCharacter::RotationToMovement() {
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	GetWorldTimerManager().ClearTimer(ViewModDelay);
}

void AJCharacter::RotationToAttack()
{
	//一旦攻击，角色就朝向攻击方向，并延迟1.0f秒
	GetWorldTimerManager().SetTimer(ViewModDelay, this, &AJCharacter::RotationToMovement, 1.0f);
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = true;
}

void AJCharacter::PrimaryInteract()
{
	InteractionComp->PrimaryInteract();
}