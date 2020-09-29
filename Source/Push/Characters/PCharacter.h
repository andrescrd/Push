// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PCharacter.generated.h"

UCLASS()
class PUSH_API APCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APCharacter();

protected:
	FTimerHandle TimerHandle_StartPush;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent *CameraComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent *SpringComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPHealthComponent *HealthComp;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class APProjectile> ProjectileClass;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void Rotate(float Value);

	UFUNCTION(BlueprintCallable)
	void Push();
	UFUNCTION(BlueprintCallable)
	void StartPush();
	UFUNCTION(BlueprintCallable)
	void ShowLineTrace();

	UFUNCTION()
	void HandleHealthDamage(class UPHealthComponent *OwnerHealthComp, int Lifes, const class UDamageType *DamageType, class AController *InstigatedBy, AActor *DamageCauser);

	void DoPosses();

public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void UnPossessed() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	//Properties
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float RotationVelocity;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float PushForce;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsPushing;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsShowingLineTrace;

	UFUNCTION(BlueprintCallable)
	void StartPosses();
	UFUNCTION(BlueprintCallable)
	bool GetIsAlive();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPush(class ACharacter *ActorPushed);
	UFUNCTION(BlueprintImplementableEvent)
	void OnDie();
};
