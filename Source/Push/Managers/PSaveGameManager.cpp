// Fill out your copyright notice in the Description page of Project Settings.


#include "PSaveGameManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

UPSaveGameManager::UPSaveGameManager() 
{
    SaveSlotName = TEXT("PSlot");
    UserIndex = 0;    
}