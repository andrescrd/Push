// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnHealthChangedSignature, UPHealthComponent *, HealthComp, int, Lifes, const class UDamageType *, DamageType, class AController *, InstigatedBy, AActor *, DamageCauser);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PUSH_API UPHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPHealthComponent();

protected:
	UPROPERTY(BlueprintReadOnly)
	int32 Lifes;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 DefaultLifes;

	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleTakeAnyDamage(AActor *DamagedActor, float Damage, const class UDamageType *DamageType, class AController *InstigatedBy, AActor *DamageCauser);

public:
	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedSignature OnHealthChanged;

	UFUNCTION(BlueprintCallable)
	int32 GetLifes();
	UFUNCTION(BlueprintCallable)
	void AddLifes(int32 NumberLifes);
};
