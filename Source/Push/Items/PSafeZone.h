// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSafeZone.generated.h"

UCLASS()
class PUSH_API APSafeZone : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APSafeZone();

protected:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent *BoxComp;

	virtual void BeginPlay() override;

public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnActorOverlap(AActor* OtherActor);
};