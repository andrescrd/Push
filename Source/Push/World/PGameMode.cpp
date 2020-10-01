
#include "PGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Push/Characters/PCharacter.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
#include "PGameInstance.h"
#include "Engine/World.h"

APGameMode::APGameMode()
{
    CurrentGameState = EGameState::Unknow;
    MaxNumberOfBots = 3;
    ActorsInSafeZone = 0;

    DefaultPawnClass = NULL;

    PrimaryActorTick.bStartWithTickEnabled = true;
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 1.f;
}

void APGameMode::BeginPlay()
{
    Super::BeginPlay();

    SpawnCharacterSelected();
    SetCurrentGameState(EGameState::Preparing);
}

void APGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (CurrentGameState == EGameState::Preparing)
        return;

    if (!IsPlayerAlive())
        SetCurrentGameState(EGameState::GameOver);
}

void APGameMode::AddActorToSafeZone(class AActor *OtherActor)
{
    if (APCharacter *Character = Cast<APCharacter>(OtherActor))
    {
        ActorsInSafeZone++;

        if (GetNumberOfCharacters() == ActorsInSafeZone)
            SetCurrentGameState(EGameState::Won);
    }
}

void APGameMode::RemoveActorFromSafeZone(class AActor *OtherActor)
{
    if (APCharacter *Character = Cast<APCharacter>(OtherActor))
        ActorsInSafeZone--;
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

void APGameMode::SpawnCharacterSelected()
{
    if (UPGameInstance *GI = GetWorld()->GetGameInstance<UPGameInstance>())
    {
        APlayerController *PC = UGameplayStatics::GetPlayerController(this, 0);

        FActorSpawnParameters Parameters;
        Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod ::AlwaysSpawn;
        AActor *CurrentPlayer = FindPlayerStart(nullptr);
        APCharacter *CurrentCharacter = GetWorld()->SpawnActor<APCharacter>(GI->GetPlayerSetup().CharacterClass, CurrentPlayer->GetTransform(), Parameters);

        PC->Possess(CurrentCharacter);
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

        GetWorldTimerManager().SetTimer(TimerHandle_InitGame, this, &APGameMode::InitPlayGame, 2.f, false);
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

        if (SpectatingViewpointClass)
        {
            TArray<AActor *> ReturnedActors;
            UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);

            AActor *NewViewTarget = nullptr;
            if (ReturnedActors.Num() > 0)
                NewViewTarget = ReturnedActors[0];

            GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(NewViewTarget, 2.f, EViewTargetBlendFunction::VTBlend_Cubic);
        }
    }
    break;

    case EGameState::Unknow:
    default:
        break;
    }
}
