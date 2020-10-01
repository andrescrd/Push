// Fill out your copyright notice in the Description page of Project Settings.

#include "PGameInstance.h"
#include "Push/Managers/PLevelManager.h"
#include "Push/Managers/PSaveGameManager.h"

void UPGameInstance::Init()
{
    Super::Init();
}

class UPSaveGameManager *UPGameInstance::SavegameManager()
{
    return IsValid(SavegameManagerInstance) ? SavegameManagerInstance : SavegameManagerInstance = NewObject<UPSaveGameManager>(this, FName("SavegameManager"));
}

class APLevelManager *UPGameInstance::GetLevelManager() const
{
    return IsValid(LevelManager) ? LevelManager :  LevelManager = NewObject<APLevelManager>(this, LevelManagerClass, TEXT("LevelManager"));
}

void UPGameInstance::SetPlayerClass(TSubclassOf<APCharacter> CharacterClass)
{
    PlayerSetup.CharacterClass = CharacterClass;
}

void UPGameInstance::SetLevel(int Level)
{
    PlayerSetup.Level = Level;
}

FPlayerSetup UPGameInstance::GetPlayerSetup()
{
    return PlayerSetup;
}
