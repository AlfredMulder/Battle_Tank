// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming states
UENUM()
enum class EFiringState : uint8
{
	Locked,
	Aiming,
	Reloading
};

// Forward declarations
class UTankBarrel;
class UTankTurret;

// Holds barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent final : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

	// TODO add SetTurretReference

	auto AimAt(FVector HitLocation, float LaunchSpeed) const -> void;

	// Reference to BlueprintCallable method
	auto SetBarrelReference(UTankBarrel* BarrelToSet) -> void;

	// Reference to BlueprintCallable method
	auto SetTurretReference(UTankTurret* TurretToSet) -> void;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Aiming;
	
private:
	// Explicit pointer on Barrel object
	UTankBarrel* Barrel = nullptr;

	// Explicit pointer on Turret object
	UTankTurret* Turret = nullptr;

	auto MoveBarrelTowards(FVector AimDirection) const -> void;
};
