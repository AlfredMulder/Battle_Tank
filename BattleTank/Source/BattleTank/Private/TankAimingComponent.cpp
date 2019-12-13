// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

auto UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) -> void
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

auto UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet) -> void
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}

auto UTankAimingComponent::AimAt(const FVector HitLocation, const float LaunchSpeed) const -> void
{
	if (!Barrel) { return; }

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
		// TODO report bug
	);

	if (bHaveAimSolution)
	{
		const auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}

	// If no solution found do nothing
}

auto UTankAimingComponent::MoveBarrelTowards(const FVector AimDirection) const -> void
{
	// Work-out difference between current barrel rotation, and AimDirection
	const auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	const auto AimAsRotator = AimDirection.Rotation();
	const auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}
