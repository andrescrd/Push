// Fill out your copyright notice in the Description page of Project Settings.

#include "PCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Push/Components/PHealthComponent.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Push/Items/PProjectile.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"

// Sets default values
APCharacter::APCharacter()
{
	RotationVelocity = 45.f;
	PushForce = 1000.f;
	IsPushing = false;
	IsShowingLineTrace = false;

	SpringComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringComp"));
	SpringComp->SetupAttachment(RootComponent);
	SpringComp->SetRelativeRotation(FRotator(-30, 0, 0));
	SpringComp->bEnableCameraLag = true;
	SpringComp->bEnableCameraRotationLag = true;
	SpringComp->CameraLagSpeed = 3.f;
	SpringComp->CameraRotationLagSpeed = 3.f;
	SpringComp->TargetArmLength = 1500.f;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringComp, USpringArmComponent::SocketName);

	HealthComp = CreateDefaultSubobject<UPHealthComponent>(TEXT("HealthComp"));

	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HealthComp)
		HealthComp->OnHealthChanged.AddDynamic(this, &APCharacter::HandleHealthDamage);
}

void APCharacter::UnPossessed()
{
	Super::UnPossessed();

	if (IsShowingLineTrace)
		IsShowingLineTrace = false;
}

void APCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsShowingLineTrace)
	{
		FHitResult OutHit;
		FVector Start = GetActorLocation();
		FVector End = (GetActorForwardVector() * 3000.f) + GetActorLocation();

		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);
		FCollisionResponseParams ResponseParam;
		ResponseParam.CollisionResponse.SetResponse(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);
		GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_WorldDynamic, CollisionParams, ResponseParam);

		if (OutHit.bBlockingHit)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));

			DrawDebugDirectionalArrow(GetWorld(), OutHit.TraceStart, OutHit.ImpactPoint, 512.f, FColor::Green, false, -1.0, 0, 5);
		}
		else
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, -1.0, 0, 5);
		}
	}
}

// Called to bind functionality to input
void APCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &APCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Rotate", this, &APCharacter::Rotate);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &APCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &APCharacter::StopJumping);
	PlayerInputComponent->BindAction("Push", EInputEvent::IE_Pressed, this, &APCharacter::StartPush);
	PlayerInputComponent->BindAction("ShowLine", EInputEvent::IE_Pressed, this, &APCharacter::ShowLineTrace);
}

void APCharacter::MoveForward(float Value)
{
	FVector Forward = GetActorForwardVector();
	AddMovementInput(Forward, Value, false);
}

void APCharacter::Rotate(float Value)
{
	float NewRotation = GetWorld()->GetDeltaSeconds() * Value * RotationVelocity * -1;
	AddControllerYawInput(NewRotation);
}

void APCharacter::StartPush()
{
	if (!IsPushing)
	{
		GetWorldTimerManager().SetTimer(TimerHandle_StartPush, this, &APCharacter::Push, 0.5f, false);
	}

	IsPushing = true;
}

void APCharacter::ShowLineTrace()
{
	IsShowingLineTrace = !IsShowingLineTrace;
}

void APCharacter::Push()
{
	IsPushing = false;

	if (ProjectileClass)
	{
		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.Instigator = GetInstigator();
		APProjectile *Projectile = GetWorld()->SpawnActor<APProjectile>(ProjectileClass, GetActorLocation(), FRotator::ZeroRotator, Params);

		if (Projectile)
		{
			Projectile->Fire(GetActorForwardVector());
		}
	}
}

void APCharacter::HandleHealthDamage(UPHealthComponent *OwnerHealthComp, int Lifes, const class UDamageType *DamageType, class AController *InstigatedBy, AActor *DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("character was hurted"));

	if (!GetIsAlive())
	{
		UE_LOG(LogTemp, Warning, TEXT("Character Die"));
		// GetCharacterMovement()->StopMovementImmediately();
		// GetCharacterMovement()->DisableMovement();
		// GetMesh()->SetSimulatePhysics(true);
		//Call to BP event
		OnDie();
	}
}

void APCharacter::StartPosses()
{
	APlayerController *PC = GetWorld()->GetFirstPlayerController();
	PC->SetViewTargetWithBlend(this, 2.f, EViewTargetBlendFunction::VTBlend_Cubic);
	PC->SetCinematicMode(true, false, false, true, true);

	FTimerHandle TimerHandle_Posses;
	GetWorldTimerManager().SetTimer(TimerHandle_Posses, this, &APCharacter::DoPosses, 2.f, false);
}

void APCharacter::DoPosses()
{
	APlayerController *PC = GetWorld()->GetFirstPlayerController();
	PC->Possess(this);
	PC->SetCinematicMode(false, false, false, true, true);
}

bool APCharacter::GetIsAlive()
{
	return HealthComp && HealthComp->GetLifes() > 0;
}