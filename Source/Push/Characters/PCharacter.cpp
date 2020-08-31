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

// Sets default values
APCharacter::APCharacter()
{
	RotationVelocity = 45.f;
	Velocity = 1000.f;
	PushForce = 1000.f;

	GetCharacterMovement()->MaxWalkSpeed = Velocity;

	SpringComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringComp"));
	SpringComp->SetupAttachment(RootComponent);
	SpringComp->SetRelativeRotation(FRotator(-30,0 , 0));
	SpringComp->TargetArmLength = 800.f;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringComp, USpringArmComponent::SocketName);

	PushZoneComp = CreateDefaultSubobject<UBoxComponent>(TEXT("PushZoneComp"));
	PushZoneComp->SetBoxExtent(FVector(32.f));
	PushZoneComp->SetRelativeLocation(FVector(80.f, 0, 0));
	PushZoneComp->SetupAttachment(RootComponent);

	HealthComp = CreateDefaultSubobject<UPHealthComponent>(TEXT("HealthComp"));
}

// Called when the game starts or when spawned
void APCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(HealthComp)
		HealthComp->OnHealthChanged.AddDynamic(this,&APCharacter::HandleHealthDamage);
}

// Called to bind functionality to input
void APCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &APCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Rotate", this, &APCharacter::Rotate);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &APCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &APCharacter::StopJumping);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &APCharacter::StopJumping);
	PlayerInputComponent->BindAction("Push", EInputEvent::IE_Pressed, this, &APCharacter::Push);
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

void APCharacter::Push()
{
	TArray<AActor *> OverlppedActors;
	PushZoneComp->GetOverlappingActors(OverlppedActors, ACharacter::StaticClass());

	for (int i = 0; i < OverlppedActors.Num(); i++)
	{
		ACharacter *SingleActor = Cast<ACharacter>(OverlppedActors[i]);

		if (SingleActor != this)
		{
			FVector LunchVelocity = GetActorForwardVector() * PushForce;
			SingleActor->LaunchCharacter(LunchVelocity, true, true);

			//Call to BP event
			OnPush(SingleActor);
		}
	}
}

void APCharacter::HandleHealthDamage(UPHealthComponent * OwnerHealthComp, int Lifes, const class UDamageType * DamageType, class AController * InstigatedBy, AActor * DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("character was hurted"));
}
