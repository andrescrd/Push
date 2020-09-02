
#include "PGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Push/Characters/PCharacter.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"

APGameMode::APGameMode()
{
    CurrentGameState = EGameState::Unknow;
    MaxNumberOfBots = 3;

    PrimaryActorTick.bStartWithTickEnabled = true;
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 1.f;
}

void APGameMode::BeginPlay()
{
    Super::BeginPlay();
    SetCurrentGameState(EGameState::Preparing);
}

void APGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (CurrentGameState == EGameState::Preparing)
        return;

    if (!CheckIsAnyCharacterAlive())
    {
        SetCurrentGameState(EGameState::Won);
    }
    else if (!IsPlayerAlive())
    {
        SetCurrentGameState(EGameState::GameOver);
    }
}

EGameState APGameMode::GetCurrentGameState() const
{
    return CurrentGameState;
}

int32 APGameMode::GetNumberOfCharacters()
{
    return AllCharacters.Num();
}

void APGameMode::SetCurrentGameState(EGameState NewState)
{
    if (CurrentGameState == NewState)
        return;

    CurrentGameState = NewState;
    HandleGameState(CurrentGameState);

    //call blueprint event
    OnGameStateChange(CurrentGameState);
}

void APGameMode::DisableAllCharacterMovement(TArray<class APCharacter *> Characters)
{
    for (int32 i = 0; i < Characters.Num(); i++)
    {
        Characters[i]->GetCharacterMovement()->DisableMovement();
    }
}

void APGameMode::InitPlayGame()
{
    SetCurrentGameState(EGameState::Playing);
}

bool APGameMode::CheckIsAnyCharacterAlive()
{
    bool IsAnyAlive = false;

    for (int32 i = 0; i < AllCharacters.Num(); i++)
    {
        if (AllCharacters[i]->GetIsAlive() && !AllCharacters[i]->IsPlayerControlled())
        {
            IsAnyAlive = true;
            break;
        }
    }

    return IsAnyAlive;
}

bool APGameMode::IsPlayerAlive()
{
    APCharacter *CurrentPlayer = Cast<APCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
    return CurrentPlayer ? CurrentPlayer->GetIsAlive() : false;
}

void APGameMode::HandleGameState(EGameState NewState)
{
    switch (NewState)
    {
    case EGameState::Preparing:
    {
        if (APlayerController *PC = UGameplayStatics::GetPlayerController(this, 0))
            PC->SetCinematicMode(true, false, false, true, true);

        GetWorldTimerManager().SetTimer(TimerHandle_InitGame, this, &APGameMode::InitPlayGame, 5.f, false);
    }
    break;
    case EGameState::Playing:
    {
        if (APlayerController *PC = UGameplayStatics::GetPlayerController(this, 0))
            PC->SetCinematicMode(false, false, false, true, true);

        TArray<AActor *> Actors;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), APCharacter::StaticClass(), Actors);

        for (auto Actor : Actors)
        {
            if (APCharacter *CurrentCharacter = Cast<APCharacter>(Actor))
            {
                CurrentCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
                AllCharacters.AddUnique(CurrentCharacter);
            }
        }
    }
    break;

    case EGameState::Won:
    case EGameState::Draw:
    case EGameState::GameOver:
    {
        DisableAllCharacterMovement(AllCharacters);

        if (APlayerController *PC = UGameplayStatics::GetPlayerController(this, 0))
            PC->SetCinematicMode(true, false, false, true, true);
    }
    break;

    case EGameState::Unknow:
    default:
        break;
    }
}
