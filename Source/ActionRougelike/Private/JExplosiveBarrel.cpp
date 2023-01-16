// Fill out your copyright notice in the Description page of Project Settings.


#include "JExplosiveBarrel.h"
#include "JMagicProjectile.h"


// Sets default values
AJExplosiveBarrel::AJExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	MeshComp->SetSimulatePhysics(true);
	RootComponent = MeshComp;
	 

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForceComp->SetupAttachment(MeshComp);
	//影响worldDynamic
	RadialForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
	RadialForceComp->SetAutoActivate(false);
	RadialForceComp->Radius = 750.0f;
	//强度,忽略物理性质
	RadialForceComp->ImpulseStrength = 1000.0f;
	RadialForceComp->bImpulseVelChange = true;

	//shift+alt+s 搜索用法
	MeshComp->OnComponentHit.AddDynamic(this, &AJExplosiveBarrel::OnActorHit);

	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");
	AudioComp->SetupAttachment(RootComponent);

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(RootComponent);

}


void AJExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Log, TEXT("Get a Hit!"));
	UE_LOG(LogTemp, Log, TEXT("%s"), *OtherActor->GetClass()->GetName());

	FString Target = "MagicProjectileBP_C";
	if (OtherActor->GetClass()->GetName() == Target) {
		RadialForceComp->FireImpulse();
		GetWorldTimerManager().SetTimer(DestroyTimeHandle,this,&AJExplosiveBarrel::Destroy,1.0f,false);
	}

	//if (OtherActor->Implements<AJMagicProjectile>()) {
	//	UE_LOG(LogTemp, Log, TEXT("right"));
	//}

}

void AJExplosiveBarrel::Destroy()
{
	GetWorld()->DestroyActor(this);
}

