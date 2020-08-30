// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPowerup.generated.h"

UCLASS()
class PUSH_API APPowerup : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APPowerup();

protected:

	FTimerHandle TimerHandle_PowerupTick;
	int32 TotalTickProccesed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Interval;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 TotalNroTick;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void TickPowerup();
public:
	void ActivatedPowerup(class AActor* ActivatorActor);

	UFUNCTION(BlueprintImplementableEvent)
	void OnActivated(class AActor* ActivatorActor);
	UFUNCTION(BlueprintImplementableEvent)
	void OnPowerupTicked();
	UFUNCTION(BlueprintImplementableEvent)
	void OnExpired();
};
