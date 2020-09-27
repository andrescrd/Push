// Fill out your copyright notice in the Description page of Project Settings.


#include "PExplosive.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Push/Components/PHealthComponent.h"

// Sets default values
APExplosive::APExplosive()
{
	bIsActive = false;
	TimeToExplode = 3;
	ExplosionImpulse = 400;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	RootComponent = MeshComp;

	RadialComp = CreateAbstractDefaultSubobject<URadialForceComponent>(TEXT("RadialComp"));
	RadialComp->SetupAttachment(MeshComp);
	RadialComp->Radius = 250.f;	
	RadialComp->bImpulseVelChange = true;
	RadialComp->bAutoActivate = false;
	RadialComp->bIgnoreOwningActor = true;

	HealthComp = CreateDefaultSubobject<UPHealthComponent>(TEXT("HealthComp"));	
}

// Called when the game starts or when spawned
void APExplosive::BeginPlay()
{
	Super::BeginPlay();

	if (HealthComp)
		HealthComp->OnHealthChanged.AddDynamic(this, &APExplosive::HandleHealthDamage);
}

void APExplosive::Explode()
{
	FVector BoostItensity = FVector::UpVector * ExplosionImpulse;
	MeshComp->AddImpulse(BoostItensity, NAME_None, true);

	RadialComp->FireImpulse();
	OnExplode();
}

void APExplosive::HandleHealthDamage(UPHealthComponent* OwnerHealthComp, int Lifes, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (bIsActive)
		return;

	bIsActive = true;
	OnActivate();
	GetWorldTimerManager().SetTimer(TimerHandle_ExplosionCounter, this, &APExplosive::Explode, TimeToExplode, false);
}

