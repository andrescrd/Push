// Fill out your copyright notice in the Description page of Project Settings.

#include "PPickup.h"
#include "Components/SphereComponent.h"
#include "Components/DecalComponent.h"
#include "Engine/World.h"
#include "PPowerup.h"
#include "TimerManager.h"

// Sets default values
APPickup::APPickup()
{
	ColdownDuration = 10.f;

	SphereCcomp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCcomp"));
	SphereCcomp->SetSphereRadius(75.f);
	RootComponent = SphereCcomp;

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->SetRelativeRotation(FRotator(90,0,0));
	DecalComp->DecalSize = FVector(65.f,75.f,75.f);
	DecalComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APPickup::BeginPlay()
{
	Super::BeginPlay();
	Respawn();
}

void APPickup::Respawn() 
{
	if(PowerupClass == nullptr)
		return;

	FActorSpawnParameters  Parameters;
	Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod ::AlwaysSpawn;

	CurrentPowerupInstance = GetWorld()->SpawnActor<APPowerup>(PowerupClass, GetActorTransform(), Parameters);
}

void APPickup::NotifyActorBeginOverlap(AActor *OtherActor) 
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if(CurrentPowerupInstance)
	{
		CurrentPowerupInstance->ActivatedPowerup(OtherActor);
		CurrentPowerupInstance = nullptr;

		GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &APPickup::Respawn, ColdownDuration);
	}
}
