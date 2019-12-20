// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

auto UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction) -> void
{
	if (ensure((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds))
	{
		FiringState = EFiringState::Reloading;
	}
	else if (BIsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

auto UTankAimingComponent::BIsBarrelMoving() const -> bool
{
	if (!ensure(Barrel)) { return false; }
	const auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);
}

auto UTankAimingComponent::BeginPlay() -> void
{
	// So that first is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

auto UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) -> void
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

auto UTankAimingComponent::AimAt(const FVector HitLocation) -> void
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	const auto StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	const auto bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace // Parameter must be present to prevent bug
	);

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	// If no solution found do nothing
}

auto UTankAimingComponent::MoveBarrelTowards(const FVector AimDirection) const -> void
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }

	// Work-out difference between current barrel rotation, and AimDirection
	const auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	const auto AimAsRotator = AimDirection.Rotation();
	const auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}


auto UTankAimingComponent::Fire() -> void
{
	if (FiringState != EFiringState::Reloading)
	{
		// Spawn a projectile at the socket location on the barrel
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		const auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}