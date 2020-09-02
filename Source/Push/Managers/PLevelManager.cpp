// Fill out your copyright notice in the Description page of Project Settings.

#include "PLevelManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

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
    FName CurrentLevelName = CleanLevelString(GetWorld());
    FLevelStruct Level;

    for (int32 index = 0; index < Levels.Num(); index++)
    {
        if (Levels[index].LevelName.IsEqual(CurrentLevelName))
        {
            Level = (index + 1 == Levels.Num()) ? Levels[0] : Levels[index + 1];
            break;
        }
    }

    return Level;
}

void APLevelManager::LoadNextLevel()
{
    FLevelStruct NextLevel = GetNextLevel();

    for (int32 index = 0; index < Levels.Num(); index++)
    {
        if (NextLevel.LevelName.IsEqual(Levels[index].LevelName))
        {
            UGameplayStatics::OpenLevel(this, NextLevel.LevelName);
            break;
        }
    }
}

void APLevelManager::LoadLevel(FName LevelNameToLoad)
{
    // FName FullName = TEXT("Map/");
    // FullName.AppendString(LevelNameToLoad.ToString());
    UGameplayStatics::OpenLevel(GetWorld(), LevelNameToLoad, true);
}


FName APLevelManager::CleanLevelString(UObject* context)
{
    FString Prefix = GEngine->GetWorldFromContextObject(context)->StreamingLevelsPrefix;
	FString LevelName = GetWorld()->GetMapName();
	return FName(*LevelName.RightChop(Prefix.Len()));
}
