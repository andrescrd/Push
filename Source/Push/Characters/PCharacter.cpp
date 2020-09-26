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

// Sets default values
APCharacter::APCharacter()
{
	RotationVelocity = 45.f;
	PushForce = 1000.f;
	IsPushing = false;

	SpringComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringComp"));
	SpringComp->SetupAttachment(RootComponent);
	SpringComp->SetRelativeRotation(FRotator(-30, 0, 0));
	SpringComp->bEnableCameraLag = true;
	SpringComp->bEnableCameraRotationLag = true;
	SpringComp->CameraLagSpeed = 5.f;
	SpringComp->CameraRotationLagSpeed = 5.f;
	SpringComp->TargetArmLength = 800.f;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringComp, USpringArmComponent::SocketName);

	PushZoneComp = CreateDefaultSubobject<UBoxComponent>(TEXT("PushZoneComp"));
	PushZoneComp->SetBoxExtent(FVector(100.f));
	PushZoneComp->SetRelativeLocation(FVector(0, 0, 0));
	PushZoneComp->SetupAttachment(RootComponent);

	HealthComp = CreateDefaultSubobject<UPHealthComponent>(TEXT("HealthComp"));
}

// Called when the game starts or when spawned
void APCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HealthComp)
		HealthComp->OnHealthChanged.AddDynamic(this, &APCharacter::HandleHealthDamage);
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

void APCharacter::Push()
{
	IsPushing = false;

	TArray<AActor *> OverlppedActors;
	PushZoneComp->GetOverlappingActors(OverlppedActors, AActor::StaticClass());

	for (int i = 0; i < OverlppedActors.Num(); i++)
	{
		APCharacter* SingleActor = Cast<APCharacter>(OverlppedActors[i]);

		if (SingleActor && SingleActor != this)
		{
			FRotator Direction = GetActorRotation();
			Direction.Pitch += 30.f;
			FVector LunchVelocity = Direction.Vector() * PushForce;
			SingleActor->LaunchCharacter(LunchVelocity, true, true);

			//Call to BP event
			OnPush(SingleActor);
		}
		else if (AActor* OtherActor = Cast<AActor>(OverlppedActors[i]))
		{
			if (OtherActor != this)
			{
				UE_LOG(LogTemp, Warning, TEXT("attack some actor"));
				UGameplayStatics::ApplyDamage(OtherActor, 1, GetOwner()->GetInstigatorController(), this, nullptr);
			}
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

bool APCharacter::GetIsAlive()
{
	return HealthComp && HealthComp->GetLifes() > 0;
}