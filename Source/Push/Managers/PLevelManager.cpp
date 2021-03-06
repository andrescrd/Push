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
            Levels[index].State = ELevelState ::Unlocked;
            UGameplayStatics::OpenLevel(World, NextLevel.LevelName);
            break;
        }
    }
}

void APLevelManager::LoadLevel(UObject *context, FName LevelNameToLoad)
{
    UWorld *World = GEngine->GetWorldFromContextObject(context);
    UE_LOG(LogTemp, Warning, TEXT("Level to load %s"), *LevelNameToLoad.ToString());
    UGameplayStatics::OpenLevel(World, LevelNameToLoad, true);
}

FName APLevelManager::CleanLevelString(UObject *context)
{
    UWorld *World = GEngine->GetWorldFromContextObject(context);
    FString Prefix = World->StreamingLevelsPrefix;
    FString LevelName = World->GetMapName();
    return FName(*LevelName.RightChop(Prefix.Len()));
}

void APLevelManager::SetLevels(TArray<FLevelStruct> NewLevels) 
{
    Levels = NewLevels;
}