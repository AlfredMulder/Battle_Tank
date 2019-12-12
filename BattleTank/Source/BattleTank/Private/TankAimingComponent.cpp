// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

auto UTankAimingComponent::AimAt(const FVector HitLocation, const float LaunchSpeed) const -> void
{
	// const auto OurTankName = GetOwner()->GetName();
	// const auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	// UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation);
	if (!Barrel) { return; }

	FVector OutLaunchVelocity;
	const auto StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	const auto bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution)
	{
		const auto AimDirection =  OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}

}

auto UTankAimingComponent::MoveBarrelTowards(const FVector AimDirection) const -> void
{
	// Work-out difference between current barrel rotation, and AimDirection
	const auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	const auto AimAsRotator = AimDirection.Rotation();
	const auto DeltaRotator = AimAsRotator - BarrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString());
	
	// Move the barrel the right amount this frame
	
	// Given a max elevation speed,and the frame time
}

auto UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet) -> void
{
	Barrel = BarrelToSet;
}

