// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PExplosive.generated.h"

UCLASS()
class PUSH_API APExplosive : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APExplosive();

protected:
	FTimerHandle TimerHandle_ExplosionCounter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* MeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class URadialForceComponent* RadialComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UPHealthComponent* HealthComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int32 TimeToExplode;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bIsActive;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float ExplosionImpulse;

	virtual void BeginPlay() override;
	void Explode();

	UFUNCTION()
	void HandleHealthDamage(class UPHealthComponent* OwnerHealthComp, int Lifes, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnActivate();
	UFUNCTION(BlueprintImplementableEvent)
	void OnExplode();
};
