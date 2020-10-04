// Fill out your copyright notice in the Description page of Project Settings.

#include "PSafeZone.h"
#include "Components/BoxComponent.h"
#include "Push/Characters/PCharacter.h"
#include "Engine/World.h"
#include "Push/World/PGameMode.h"
#include "Engine/Engine.h"

// Sets default values
APSafeZone::APSafeZone()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->InitBoxExtent(FVector(50.f));
	RootComponent = BoxComp;
}

// Called when the game starts or when spawned
void APSafeZone::BeginPlay()
{
	Super::BeginPlay();
}

void APSafeZone::NotifyActorBeginOverlap(AActor *OtherActor)
{
	for (int32 i = 0; i < CharacterClass.Num(); i++)
	{
		if (OtherActor->IsA(CharacterClass[i]))
		{
			APGameMode *GM = GetWorld()->GetAuthGameMode<APGameMode>();
			GM->AddActorToSafeZone(OtherActor);

			// call bp event
			OnOverlap(OtherActor);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Blue, FString::Printf(TEXT("It is a %s"), *OtherActor->GetName()));
		}
	}
}

void APSafeZone::NotifyActorEndOverlap(AActor *OtherActor)
{
	for (int32 i = 0; i < CharacterClass.Num(); i++)
	{
		if (OtherActor->IsA(CharacterClass[i]))
		{
			APGameMode *GM = GetWorld()->GetAuthGameMode<APGameMode>();
			GM->RemoveActorFromSafeZone(OtherActor);

			// call bp event
			OnEndOverlap(OtherActor);
		}	
	}
}
