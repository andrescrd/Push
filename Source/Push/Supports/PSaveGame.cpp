// Fill out your copyright notice in the Description page of Project Settings.


#include "PSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

UPSaveGame::UPSaveGame() 
{
    SaveSlotName = TEXT("PSlot");
    UserIndex = 0;    
}