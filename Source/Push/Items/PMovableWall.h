// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PMovableWall.generated.h"

USTRUCT(BlueprintType)
struct FDataWall
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EndPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AActor *ActorToMove;
};

UCLASS()
class PUSH_API APMovableWall : public AActor
{
	GENERATED_BODY()

public:
	APMovableWall();

protected:
	bool IsActive;
	TArray<FDataWall> ActorsToMove;
	TArray<class APMovableWall *> MovableWalls;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<class AActor *> GroupComp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<class AActor *> InverseGroupComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UTimelineComponent *MyTimeline;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UBoxComponent *ActivatorComp;

	void SetupTimeline();

public:
	UPROPERTY(EditAnywhere, Category = "Timeline")
	class UCurveFloat *Curve;
	UPROPERTY(EditAnywhere, Category = "Timeline")
	float ZOffset;

	bool GetIsActive();

	UFUNCTION()
	void HandleBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION()
	void HandleEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnTimelineFloatReturn(float Value);
	UFUNCTION()
	void OnTimelineFinished();

	UFUNCTION(BlueprintCallable)
	void StartMovement();

	UFUNCTION(BlueprintCallable)
	void ReverseMovement();

	UFUNCTION(BlueprintImplementableEvent)
	void OnActivated();
};
