// Fill out your copyright notice in the Description page of Project Settings.


#include "PProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
APProjectile::APProjectile()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	CollisionComp->InitSphereRadius(15.0f);
	RootComponent = CollisionComp;

	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileComp->SetUpdatedComponent(CollisionComp);
	ProjectileComp->InitialSpeed = 3000.0f;
	ProjectileComp->MaxSpeed = 3000.0f;
	ProjectileComp->bRotationFollowsVelocity = true;
	ProjectileComp->bShouldBounce = true;
	ProjectileComp->Bounciness = 1.f;
}

// Called when the game starts or when spawned
void APProjectile::BeginPlay()
{
	Super::BeginPlay();

}

void APProjectile::Fire(const FVector Direction)
{
	ProjectileComp->Velocity = Direction * ProjectileComp->InitialSpeed;
}

void APProjectile::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("projectile hit %s"), *Other->GetName());
}
