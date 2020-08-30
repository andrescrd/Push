// Fill out your copyright notice in the Description page of Project Settings.

#include "PPowerup.h"
#include "TimerManager.h"

// Sets default values
APPowerup::APPowerup()
{
	Interval = 0.f;
	TotalNroTick = 0;
}

// Called when the game starts or when spawned
void APPowerup::BeginPlay()
{
	Super::BeginPlay();
}

void APPowerup::TickPowerup()
{
	TotalTickProccesed++;

	OnPowerupTicked();

	if (TotalTickProccesed >= TotalNroTick)
	{
		OnExpired();
		GetWorldTimerManager().ClearTimer(TimerHandle_PowerupTick);
	}
}

void APPowerup::ActivatedPowerup(AActor* ActivatorActor)
{
	OnActivated(ActivatorActor);

	if (Interval > 0)
	{
		GetWorldTimerManager().SetTimer(TimerHandle_PowerupTick, this, &APPowerup::TickPowerup, Interval, true);
	}
	else
	{
		TickPowerup();
	}
}
