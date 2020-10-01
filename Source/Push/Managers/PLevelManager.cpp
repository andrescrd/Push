// Fill out your copyright notice in the Description page of Project Settings.

#include "PLevelManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Engine.h"


APLevelManager::APLevelManager() 
{
    
}


TArray<FLevelStruct> APLevelManager::GetLevels()
{
    return Levels;
}

FLevelStruct APLevelManager::GetFirstLavel()
{
    return Levels[0];
}

FLevelStruct APLevelManager::GetNextLevel(UObject *context)
{    
    FName CurrentLevelName = CleanLevelString(context);
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

void APLevelManager::LoadNextLevel(UObject *context)
{
    FLevelStruct NextLevel = GetNextLevel(context);
    UWorld *World = GEngine->GetWorldFromContextObject(context);

    for (int32 index = 0; index < Levels.Num(); index++)
    {
        if (NextLevel.LevelName.IsEqual(Levels[index].LevelName))
        {
            UGameplayStatics::OpenLevel(World, NextLevel.LevelName);
            break;
        }
    }
}

void APLevelManager::LoadLevel(UObject *context, FName LevelNameToLoad)
{
    UWorld *World = GEngine->GetWorldFromContextObject(context);
    UGameplayStatics::OpenLevel(World, LevelNameToLoad, true);
}

FName APLevelManager::CleanLevelString(UObject *context)
{
    UWorld *World = GEngine->GetWorldFromContextObject(context);
    FString Prefix = World->StreamingLevelsPrefix;
    FString LevelName = World->GetMapName();
    return FName(*LevelName.RightChop(Prefix.Len()));
}