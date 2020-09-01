
#include "PGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Push/Characters/PCharacter.h"
#include "Engine/World.h"

APGameMode::APGameMode()
{
    CurrentGameState = EGameState::Playing;
}

void APGameMode::BeginPlay()
{
    Super::BeginPlay();

    TArray<AActor *> Actors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APCharacter::StaticClass(), Actors);

    for (auto Actor : Actors)
    {
        if (APCharacter *CurrentCharacter = Cast<APCharacter>(Actor))
            AllCharacters.AddUnique(CurrentCharacter);
    }
}

EGameState APGameMode::GetCurrentGameState() const
{
    return CurrentGameState;
}

void APGameMode::SetCurrentGameState(EGameState NewState)
{
    CurrentGameState = NewState;
}

void APGameMode::HandleGameState(EGameState NewState)
{
    switch (NewState)
    {
    case EGameState::Playing:
        /* code */
        break;

    case EGameState::Won:
        /* code */
        break;
    case EGameState::Draw:
        /* code */
        break;

    case EGameState::GameOver:
        /* code */
        break;

    case EGameState::Unknow:
    default:
        break;
    }
}
