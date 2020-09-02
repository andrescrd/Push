// Fill out your copyright notice in the Description page of Project Settings.

#include "PLevelManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

TArray<FName> APLevelManager::GetLevels()
{
    return Levels;
}

FName APLevelManager::GetFirstLavel() 
{
    return Levels[0];
}

FName APLevelManager::GetNextLevel() 
{    
    for (int32 index = 0; index < Levels.Num(); index++)
    {
        if(CurrentLevel.IsEqual(Levels[index]))
        {
            if (index + 1 == Levels.Num())
            {
             return Levels[0];
            }
            else
            {
                return Levels[index +1];
            }
        }
    }    

}

void APLevelManager::LoadLevel(FName LevelNameToLoad)
{
    // FName FullName = TEXT("Map/");
    // FullName.AppendString(LevelNameToLoad.ToString());
    UGameplayStatics::OpenLevel(GetWorld(),LevelNameToLoad, true);
}
