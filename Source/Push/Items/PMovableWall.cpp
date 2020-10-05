// Fill out your copyright notice in the Description page of Project Settings.

#include "PMovableWall.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APMovableWall::APMovableWall()
{
	ZOffset = -250.f;
	USceneComponent *Dummy = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy"));
	RootComponent = Dummy;

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

	TArray<AActor *> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APMovableWall::StaticClass(), OutActors);

	for (int32 i = 0; i < OutActors.Num(); i++)
	{
		if (OutActors[i] != this)
			MovableWalls.Add(Cast<APMovableWall>(OutActors[i]));
	}
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

		for (int32 i = 0; i < GroupComp.Num(); i++)
		{
			FDataWall Moveable;
			Moveable.ActorToMove = GroupComp[i];
			Moveable.StartPosition = GroupComp[i]->GetActorLocation();
			FVector EndLocation = Moveable.StartPosition;
			EndLocation.Z += ZOffset;
			Moveable.EndPosition = EndLocation;
			Moveable.ActorToMove = GroupComp[i];
			ActorsToMove.Add(Moveable);
		}

		for (int32 i = 0; i < InverseGroupComp.Num(); i++)
		{
			FDataWall InverseMoveable;
			InverseMoveable.ActorToMove = InverseGroupComp[i];
			InverseMoveable.StartPosition = InverseGroupComp[i]->GetActorLocation();
			FVector EndLocation = InverseMoveable.StartPosition;
			EndLocation.Z -= ZOffset;
			InverseMoveable.EndPosition = EndLocation;
			InverseMoveable.ActorToMove = InverseGroupComp[i];
			ActorsToMove.Add(InverseMoveable);
		}

		MyTimeline->SetLooping(false);
		MyTimeline->SetIgnoreTimeDilation(true);
	}
}
void APMovableWall::HandleBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	for (int32 i = 0; i < MovableWalls.Num(); i++)
	{
		if (MovableWalls[i]->GetIsActive())
			return;
	}

	if (OtherActor->IsA(ACharacter::StaticClass()))
	{
		IsActive = true;
		StartMovement();

		// call bp event
		OnActivated();
	}
}

void APMovableWall::HandleEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	for (int32 i = 0; i < MovableWalls.Num(); i++)
	{
		if (MovableWalls[i]->GetIsActive())
			return;
	}

	if (OtherActor->IsA(ACharacter::StaticClass()))
	{
		IsActive = false;
		ReverseMovement();
	}
}

void APMovableWall::OnTimelineFloatReturn(float Value)
{
	for (int32 i = 0; i < ActorsToMove.Num(); i++)
	{
		ActorsToMove[i].ActorToMove->SetActorLocation(FMath::Lerp(ActorsToMove[i].StartPosition, ActorsToMove[i].EndPosition, Value));
	}
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

bool APMovableWall::GetIsActive()
{
	return IsActive;
}