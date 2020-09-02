// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PUSH_API UPBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static class APLevelManager *GetLevelManager(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable)
	static class UPGameInstance *GetOwnGameInstance(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable)
	static class APGameMode *GetOwnGameMode(const UObject* WorldContextObject);
};
