// Fill out your copyright notice in the Description page of Project Settings.

#include "PMovableWall.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Engine/Engine.h"

// Sets default values
APMovableWall::APMovableWall()
{
	ZOffset = -250.f;
	USceneComponent *Dummy = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy"));
	RootComponent = Dummy;

	GroupComp = CreateDefaultSubobject<USceneComponent>(TEXT("GroupComp"));
	GroupComp->SetupAttachment(RootComponent);

	InverseGroupComp = CreateDefaultSubobject<USceneComponent>(TEXT("InverseGroupComp"));
	InverseGroupComp->SetupAttachment(RootComponent);

	ActivatorComp = CreateDefaultSubobject<UBoxComponent>(TEXT("ActivatorComp"));
	ActivatorComp->SetupAttachment(RootComponent);

	MyTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timelines"));
}

// Called when the game starts or when spawned
void APMovableWall::BeginPlay()
{
	Super::BeginPlay();

	ActivatorComp->OnComponentBeginOverlap.AddDynamic(this, &APMovableWall::HandleBeginOverlap);
	ActivatorComp->OnComponentEndOverlap.AddDynamic(this, &APMovableWall::HandleEndOverlap);
	SetupTimeline();
}

void APMovableWall::SetupTimeline()
{
	if (Curve)
	{
		FOnTimelineFloat InterpFunction;
		FOnTimelineEvent TimelineFinished;

		InterpFunction.BindUFunction(this, FName("OnTimelineFloatReturn"));
		TimelineFinished.BindUFunction(this, FName("OnTimelineFinished"));

		MyTimeline->AddInterpFloat(Curve, InterpFunction, FName("Alpha"));
		MyTimeline->SetTimelineFinishedFunc(TimelineFinished);

		StartLocation = GroupComp->GetRelativeLocation();
		EndLocation = StartLocation;
		EndLocation.Z += ZOffset;

		InverseStartLocation = InverseGroupComp->GetRelativeLocation();
		InverseEndLocation = InverseStartLocation;
		InverseEndLocation.Z -= ZOffset;

		MyTimeline->SetLooping(false);
		MyTimeline->SetIgnoreTimeDilation(true);
	}
}

void APMovableWall::HandleBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (ACharacter *Character = Cast<ACharacter>(OtherActor))
		StartMovement();
}

void APMovableWall::HandleEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	if (ACharacter *Character = Cast<ACharacter>(OtherActor))
		ReverseMovement();
}

void APMovableWall::OnTimelineFloatReturn(float Value)
{
	GroupComp->SetRelativeLocation(FMath::Lerp(StartLocation, EndLocation, Value));
	InverseGroupComp->SetRelativeLocation(FMath::Lerp(InverseStartLocation, InverseEndLocation, Value));
}

void APMovableWall::OnTimelineFinished()
{
	//TODO: Do something here
}

void APMovableWall::StartMovement()
{
	if (Curve)
		MyTimeline->Play();
}

void APMovableWall::ReverseMovement()
{
	if (Curve)
		MyTimeline->Reverse();
}