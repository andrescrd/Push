// Fill out your copyright notice in the Description page of Project Settings.

#include "PLevelManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

TArray<FLevelStruct> APLevelManager::GetLevels()
{
    return Levels;
}

FLevelStruct APLevelManager::GetFirstLavel()
{
    return Levels[0];
}

FLevelStruct APLevelManager::GetNextLevel()
{
    FLevelStruct Level;

    for (int32 index = 0; index < Levels.Num(); index++)
    {
        if (CurrentLevel.LevelName.IsEqual(Levels[index].LevelName))
        {
            Level = (index + 1 == Levels.Num()) ? Levels[0] : Levels[index + 1];
            break;
        }
    }

    return Level;
}

void APLevelManager::LoadLevel(FName LevelNameToLoad)
{
    // FName FullName = TEXT("Map/");
    // FullName.AppendString(LevelNameToLoad.ToString());
    UGameplayStatics::OpenLevel(GetWorld(), LevelNameToLoad, true);
}
