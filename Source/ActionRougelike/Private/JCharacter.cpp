// Fill out your copyright notice in the Description page of Project Settings.


#include "JCharacter.h"
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


	UE_LOG(LogTemp, Error, TEXT("%d"), bUseControllerRotationYaw ? 1 : 0);

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
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
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
	//一旦攻击，角色就朝向攻击方向，并延迟2.0f秒
	GetWorldTimerManager().SetTimer(ViewModDelay,this,&AJCharacter::RotationToMovement,2.0f);
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = true;

	
	//设置在手上发射
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);

}

void AJCharacter::RotationToMovement() {
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}