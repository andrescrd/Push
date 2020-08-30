// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPickup.generated.h"

UCLASS()
class PUSH_API APPickup : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APPickup();

protected:
	FTimerHandle TimerHandle_RespawnTimer;
	class APPowerup* CurrentPowerupInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent *SphereCcomp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UDecalComponent *DecalComp;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TSubclassOf<class APPowerup> PowerupClass;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	float ColdownDuration;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Respawn();

public:
	virtual void NotifyActorBeginOverlap(AActor *OtherActor) override;
};
