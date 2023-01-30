// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/JBaseProjectile.h"

// Sets default values
AJBaseProjectile::AJBaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*
	* 初始化球体并设为根组件
	* 碰撞设定为Projectile预设
	* 不模拟物理
	*/
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->SetSimulatePhysics(false);
	RootComponent = SphereComp;

	//初始化运动
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0F;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0;

	//Particle
	ParticleFlyComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleFlyComp");
	ParticleFlyComp->SetupAttachment(RootComponent);
	ParticleEndComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleEndComp");
	ParticleEndComp->SetupAttachment(RootComponent);
	ParticleEndComp->SetAutoActivate(false);

	//Audio
	AudioFlyComp = CreateDefaultSubobject<UAudioComponent>("AudioFlyComp");
	AudioFlyComp->SetupAttachment(RootComponent);
	AudioFlyComp->bOverrideAttenuation = true;
	AudioEndComp = CreateDefaultSubobject<UAudioComponent>("AudioEndComp");
	AudioEndComp->SetupAttachment(RootComponent);
	AudioEndComp->bOverrideAttenuation = true;
	AudioEndComp->SetAutoActivate(false);


}

// Called when the game starts or when spawned
void AJBaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	//设置撞击
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	SphereComp->OnComponentHit.AddDynamic(this, &AJBaseProjectile::OnActorHit);
	GetWorldTimerManager().SetTimer(MaxExistTimeHandle, this, &AJBaseProjectile::ReadyToDestroy, MaxExistTime);
}


// Called every frame
void AJBaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AJBaseProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ReadyToDestroy();
}

void AJBaseProjectile::ReadyToDestroy()
{
	if (DestroyTimeHandle.IsValid()) return;

	ParticleFlyComp->SetActive(false);
	ParticleEndComp->SetActive(true);

	AudioFlyComp->SetActive(false);
	AudioEndComp->SetActive(true);

	GetWorldTimerManager().SetTimer(DestroyTimeHandle, this, &AJBaseProjectile::Destroy, TimeToDestroy);
}

void AJBaseProjectile::Destroy()
{
	GetWorld()->DestroyActor(this);
}
