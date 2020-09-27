// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PProjectile.generated.h"

UCLASS()
class PUSH_API APProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APProjectile();

protected:

	UPROPERTY(VisibleAnywhere)
		class USphereComponent* CollisionComp;
	UPROPERTY(VisibleAnywhere)
		class UProjectileMovementComponent* ProjectileComp;

	virtual void BeginPlay() override;

public:
	void Fire(const FVector Direction);
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	UFUNCTION()
		void HandleOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintImplementableEvent)
		void OnProjectileHit(const FVector Location);
};
