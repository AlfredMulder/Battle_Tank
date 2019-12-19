// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declarations
class UTankBarrel;
class AProjectile;
class UTankMovementComponent;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank final : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	auto AimAt(FVector HitLocation) const -> void;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000; // Sensible starting value of 4000 m/s

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;

	UTankBarrel* Barrel = nullptr; // TODO Remove

	auto BeginPlay() -> void override;
};
