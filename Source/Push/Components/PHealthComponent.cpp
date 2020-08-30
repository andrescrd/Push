// Fill out your copyright notice in the Description page of Project Settings.

#include "PHealthComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPHealthComponent::UPHealthComponent()
{
	DefaultLifes = 3;
}

void UPHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Lifes = DefaultLifes;
	AActor *CurrentActor = GetOwner();

	if (CurrentActor)
		CurrentActor->OnTakeAnyDamage.AddDynamic(this, &UPHealthComponent::HandleTakeAnyDamage);
}

void UPHealthComponent::HandleTakeAnyDamage(AActor *DamagedActor, float Damage, const class UDamageType *DamageType, class AController *InstigatedBy, AActor *DamageCauser)
{
	if (Lifes <= 0)
		return;

	Lifes--;
	OnHealthChanged.Broadcast(this, Lifes, DamageType, InstigatedBy, DamageCauser);
}

void UPHealthComponent::AddLifes(int NumberLifes)
{
	if (Lifes <= 0 || NumberLifes <= 0)
		return;

	Lifes++;
	OnHealthChanged.Broadcast(this, Lifes, nullptr, nullptr, nullptr);
}
