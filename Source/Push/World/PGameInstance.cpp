// Fill out your copyright notice in the Description page of Project Settings.

#include "PGameInstance.h"
#include "Push/Managers/PLevelManager.h"
#include "Push/Managers/PSaveGameManager.h"
#include "Kismet/GameplayStatics.h"

void UPGameInstance::Init()
{
    Super::Init();

    if (LevelManagerClass)
        LevelManagerInstance = NewObject<APLevelManager>(this, LevelManagerClass, TEXT("LevelManager"));

    if (LevelManagerInstance)
    {
        UPSaveGameManager *LoadedGame = Cast<UPSaveGameManager>(UGameplayStatics::LoadGameFromSlot(GetSaveGameManager()->SaveSlotName, GetSaveGameManager()->UserIndex));
        if(LoadedGame->Levels.Num() > 0)
            LevelManagerInstance->SetLevels(LoadedGame->Levels);
    }
}

void UPGameInstance::Shutdown() 
{
    GetSaveGameManager()->Levels = LevelManagerInstance->GetLevels();
    UGameplayStatics::SaveGameToSlot(GetSaveGameManager(), GetSaveGameManager()->SaveSlotName, GetSaveGameManager()->UserIndex);
}


class UPSaveGameManager *UPGameInstance::GetSaveGameManager()
{
    return IsValid(SavegameManagerInstance) ? SavegameManagerInstance : SavegameManagerInstance = NewObject<UPSaveGameManager>(this, FName("SavegameManager"));
}

class APLevelManager *UPGameInstance::GetLevelManager() const
{
    return IsValid(LevelManagerInstance) ? LevelManagerInstance : nullptr;
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
