// Fill out your copyright notice in the Description page of Project Settings.

#include "PBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "Push/World/PGameInstance.h"
#include "Push/World/PGameMode.h"
#include "GameFramework/GameMode.h"

class APLevelManager *UPBlueprintFunctionLibrary::GetLevelManager(const UObject *WorldContextObject)
{
    UPGameInstance *GI = GetOwnGameInstance(WorldContextObject);
    return GI != nullptr ? GI->GetLevelManager() : nullptr;
}

class UPGameInstance *UPBlueprintFunctionLibrary::GetOwnGameInstance(const UObject *WorldContextObject)
{
    UGameInstance *CurrentGI = UGameplayStatics::GetGameInstance(WorldContextObject);
    return CurrentGI != nullptr ? Cast<UPGameInstance>(CurrentGI) : nullptr;
}

class APGameMode *UPBlueprintFunctionLibrary::GetOwnGameMode(const UObject *WorldContextObject)
{
    AGameModeBase *CurrentGM = UGameplayStatics::GetGameMode(WorldContextObject);
    return CurrentGM != nullptr ? Cast<APGameMode>(CurrentGM) : nullptr;
}
