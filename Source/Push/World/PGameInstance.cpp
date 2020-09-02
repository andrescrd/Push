// Fill out your copyright notice in the Description page of Project Settings.

#include "PGameInstance.h"
#include "Push/Managers/PLevelManager.h"

void UPGameInstance::Init()
{
    Super::Init();    

    if (LevelManagerClass)
        LevelManager = NewObject<APLevelManager>(this,LevelManagerClass, TEXT("LevelManager"));
}

class APLevelManager *UPGameInstance::GetLevelManager() const
{
    return LevelManager;
}
