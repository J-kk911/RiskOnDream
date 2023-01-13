// Fill out your copyright notice in the Description page of Project Settings.


#include "JMagicProjectile.h"

// Sets default values
AJMagicProjectile::AJMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//初始化球体并设为根组件
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	//碰撞设定为Projectile预设
	SphereComp->SetCollisionProfileName("Projectile");

	//初始化运动
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0F;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	//初始化粒子特效
	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");

	//初始化默认资源
	//静态加载资源
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(
		TEXT("/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Primary/FX/P_Gideon_Primary_Projectile.P_Gideon_Primary_Projectile"));
	EffectComp->SetTemplate(ParticleAsset.Object);

	//依附于球碰撞体
	EffectComp->SetupAttachment(SphereComp);

	//被撞击时触发
	SphereComp->OnComponentHit.AddDynamic(this,&AJMagicProjectile::OnActorHit);

	//声音组件
	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");

	//根据距离衰减
	AudioComp->bOverrideAttenuation = true;
	//AudioComp->SetAutoActivate(false);

	IsHit = false;
	WaitTick = 30;

	//不模拟物理
	SphereComp->SetSimulatePhysics(false);
	
}

// Called when the game starts or when spawned
void AJMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DestroyCheck();
}

void AJMagicProjectile::DestroyCheck()
{
	if (IsHit) {
		WaitTick--;
		if (WaitTick == 0) {
			GetWorld()->DestroyActor(this);
		}
	}
}

void AJMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	USoundBase* sb = LoadObject<USoundBase>(nullptr,TEXT("/Game/ExampleContent/Audio/Abilities/A_Ability_MeteorImpact01.A_Ability_MeteorImpact01"));
	AudioComp->SetSound(sb);
	AudioComp->Play(); 
		
	//动态加载资源
	UParticleSystem* ps = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Primary/FX/P_Gideon_Primary_HitWorld.P_Gideon_Primary_HitWorld"));
	EffectComp->SetTemplate(ps);

	IsHit = true;
}