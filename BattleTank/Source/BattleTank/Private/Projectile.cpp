// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Adding UProjectileMovementComponent manually in Projectile_BP
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

auto AProjectile::LaunchProjectile(const float Speed) -> void
{
	auto const Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Projectile Fires at %f"), Time, Speed);
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
}
