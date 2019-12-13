// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declaration to use UTankBarrel
class UTankBarrel;

// Forward declaration to use UTankTurret
class UTankTurret;

// Forward declaration to use AProjectile
class AProjectile;

UCLASS()
class BATTLETANK_API ATank final : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	auto SetupPlayerInputComponent(class UInputComponent* InputComponent) -> void override;

	auto AimAt(FVector HitLocation) const -> void;

	// Method for using barrel component in BP
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	// Method for using turret component in BP
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet) const;

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

	// Called when the game starts or when spawned
	auto BeginPlay() -> void override;

private:
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000; // Sensible starting value of 4000 m/s

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	// Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;
	
	double LastFireTime = 0;
};
