// Fill out your copyright notice in the Description page of Project Settings.

#include "PDataManager.h"
#include "Kismet/GameplayStatics.h"
#include "Push/Managers/PSaveGameManager.h"
#include "Engine.h"

void APDataManager::SaveLevels(TArray<FLevelStruct> LevelsToSave)
{
    GetSaveGameInstance()->Levels = LevelsToSave;
    UGameplayStatics::SaveGameToSlot(GetSaveGameInstance(), GetSaveGameInstance()->SaveSlotName, GetSaveGameInstance()->UserIndex);
}

TArray<FLevelStruct> APDataManager::GetLevels()
{
    if (UPSaveGameManager *LoadedGame = Cast<UPSaveGameManager>(UGameplayStatics::LoadGameFromSlot(GetSaveGameInstance()->SaveSlotName, GetSaveGameInstance()->UserIndex)))
    {
        GEngine->AddOnScreenDebugMessage(0, 0.f, FColor::Red, FString::Printf(TEXT("Game Loaded")));
        return LoadedGame->Levels;
    }

    return TArray<FLevelStruct>::TArray();
}

void APDataManager::ClearData()
{
    GEngine->AddOnScreenDebugMessage(0, 0.f, FColor::Red, FString::Printf(TEXT("Clear Data")));
}

class UPSaveGameManager *APDataManager::GetSaveGameInstance()
{
    return IsValid(SaveGameInstance) ? SaveGameInstance : SaveGameInstance = Cast<UPSaveGameManager>(UGameplayStatics::CreateSaveGameObject(UPSaveGameManager::StaticClass()));
}
