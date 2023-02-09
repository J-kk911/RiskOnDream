// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/JMagicProjectile.h"
#include "DrawDebugHelpers.h"
#include "Character/JAttributeComponent.h"


// Sets default values
AJMagicProjectile::AJMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MovementComp->InitialSpeed = 2000.0F;

	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&AJMagicProjectile::OnActorBeginOverlap);

}


void AJMagicProjectile::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//因为是Overlap，所以可以日后增加判断是不是队友
	if (OtherActor) {
		//通过actor中能不能找到 属性组件 判断能不能接受打击
		UJAttributeComponent* AttributeComp = Cast<UJAttributeComponent>(OtherActor->GetComponentByClass(UJAttributeComponent::StaticClass()));
		if (AttributeComp) {
			if (Hit)return;
			//显示数值伤害
			DrawDebugString(GetWorld(), OtherActor->GetActorLocation(),TEXT("-20"),NULL,FColor::Red,0.5,false,1.f);
			AttributeComp->ApplyHealthChange(-20.0);
			ReadyToDestroy();
			Hit = true;
		}
	}

}




