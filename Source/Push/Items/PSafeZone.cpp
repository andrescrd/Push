// Fill out your copyright notice in the Description page of Project Settings.

#include "PSafeZone.h"
#include "Components/BoxComponent.h"
#include "Push/Characters/PCharacter.h"
#include "Engine/World.h"
#include "Push/World/PGameMode.h"

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
	if (APCharacter *CurrentCharacter = Cast<APCharacter>(OtherActor))
	{
		APGameMode *GM = GetWorld()->GetAuthGameMode<APGameMode>();
		GM->AddActorToSafeZone(CurrentCharacter);

		// call bp event
		OnOverlap(OtherActor);
	}
}

void APSafeZone::NotifyActorEndOverlap(AActor *OtherActor)
{
	if (APCharacter *CurrentCharacter = Cast<APCharacter>(OtherActor))
	{
		APGameMode *GM = GetWorld()->GetAuthGameMode<APGameMode>();
		GM->RemoveActorFromSafeZone(CurrentCharacter);

		// call bp event
		OnEndOverlap(OtherActor);
	}
}
