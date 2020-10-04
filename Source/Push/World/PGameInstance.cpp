// Fill out your copyright notice in the Description page of Project Settings.

#include "PGameInstance.h"
#include "Push/Managers/PLevelManager.h"
#include "Push/Managers/PDataManager.h"
#include "Kismet/GameplayStatics.h"

void UPGameInstance::Init()
{
    Super::Init();

    if (LevelManagerClass)
        LevelManagerInstance = NewObject<APLevelManager>(this, LevelManagerClass, TEXT("LevelManager"));

    if (LevelManagerInstance)
    {        
        if (GetDataManager()->GetLevels().Num() > 0)
            LevelManagerInstance->SetLevels(GetDataManager()->GetLevels());
    }
}

void UPGameInstance::Shutdown()
{
    GetDataManager()->SaveLevels(LevelManagerInstance->GetLevels());
}

class APLevelManager *UPGameInstance::GetLevelManager()
{
    return IsValid(LevelManagerInstance) ? LevelManagerInstance : nullptr;
}

class APDataManager *UPGameInstance::GetDataManager()
{
    return IsValid(DataManagerInstance) ? DataManagerInstance : DataManagerInstance = NewObject<APDataManager>(this, FName("DataManager"));
}