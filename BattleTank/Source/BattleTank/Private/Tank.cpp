// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankTurret.h"
#include "TankMovementComponent.h"
#include "TankAimingComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Adding UTankAimingComponent manually in Tank_BP
	// No need to protect points as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

auto ATank::SetBarrelReference(UTankBarrel* BarrelToSet) -> void
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

auto ATank::SetTurretReference(UTankTurret* TurretToSet) const -> void
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
	const auto bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	// Spawn a projectile at the socket location on the barrel
	if (Barrel && bIsReloaded)
	{
		const auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
		);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
auto ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent) -> void
{
	Super::SetupPlayerInputComponent(InputComponent);
}

auto ATank::AimAt(const FVector HitLocation) const -> void
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}
