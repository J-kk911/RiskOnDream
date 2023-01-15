// Fill out your copyright notice in the Description page of Project Settings.


#include "JItemChest.h"

// Sets default values
AJItemChest::AJItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);

	OpenTimeline = CreateDefaultSubobject<UTimelineComponent>("OpenTimeline");

	Curver = CreateDefaultSubobject<UCurveFloat>("Curver");

	//设置这条曲线
	FRichCurve RichCurve;
	FKeyHandle KeyHandle;

	KeyHandle = RichCurve.AddKey(0, 0);
	KeyHandle = RichCurve.AddKey(0.5, 110);

	Curver->FloatCurve = RichCurve;
}

// Called when the game starts or when spawned
void AJItemChest::BeginPlay()
{
	Super::BeginPlay();

	//这部分不能在构造函数里，因为curve还没绑定
	if (Curver) {
		/*
		* 函数分别通过TEXT绑定在两个变量上再传到Timeline中，注意参数类型
		* 一个是过程中
		* 一个是结束时候触发
		*/
		FOnTimelineFloat OnTimelineFloatEvent;
		FOnTimelineEvent OnTimelineFinishedEvent;

		OnTimelineFloatEvent.BindUFunction(this, TEXT("OnTimelineTick"));
		//OnTimelineFinishedEvent.BindUFunction(this, TEXT("SetState"));

		OpenTimeline->AddInterpFloat(Curver, OnTimelineFloatEvent);
		//OpenTimeline->SetTimelineFinishedFunc(OnTimelineFinishedEvent);

		//设置结束时间为最后一个关键帧
		OpenTimeline->SetTimelineLength(ETimelineLengthMode::TL_LastKeyFrame);
	}

}

// Called every frame
void AJItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJItemChest::Interact_Implementation(APawn* OperaterPawn)
{
	if (!OpenTimeline->IsPlaying()) {
		if (Open) {
			OpenTimeline->ReverseFromEnd();
		}else{
			OpenTimeline->PlayFromStart();
		}
		Open = !Open;
	}
}

void AJItemChest::OnTimelineTick(float Output)
{
	//UE_LOG(LogTemp, Warning, TEXT("output:%f"), Output);
	LidMesh->SetRelativeRotation(FRotator(Output, 0, 0));

}

