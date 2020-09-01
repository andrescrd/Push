// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PType.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	Preparing,	
	Playing,
	Won,
	Draw,
	GameOver,
	Unknow
};
