// Fill out your copyright notice in the Description page of Project Settings.


#include "PProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Push/Characters/PCharacter.h"
// Sets default values
APProjectile::APProjectile()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	CollisionComp->InitSphereRadius(15.0f);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	RootComponent = CollisionComp;

	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileComp->SetUpdatedComponent(CollisionComp);
	ProjectileComp->InitialSpeed = 3000.0f;
	ProjectileComp->MaxSpeed = 3000.0f;
	ProjectileComp->bRotationFollowsVelocity = true;
	ProjectileComp->bShouldBounce = true;
	ProjectileComp->Bounciness = 1.f;
	ProjectileComp->Friction = 0.f;
	ProjectileComp->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void APProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (CollisionComp)
		CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &APProjectile::HandleOverlap);

}

void APProjectile::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != GetOwner())
	{
		if (APCharacter* CharacaterHit = Cast<APCharacter>(OtherActor))
		{
			CharacaterHit->StartPosses();
		}
	}
}


void APProjectile::Fire(const FVector Direction)
{
	ProjectileComp->Velocity = Direction * ProjectileComp->InitialSpeed;
}

void APProjectile::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	OnProjectileHit(HitLocation);
}
