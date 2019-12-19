// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// Forward declarations.
class UTankTankAimingComponent;

/**
 * Responsible for helping the player aim.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController final : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	auto BeginPlay() -> void override;

	auto Tick(float DeltaTime) -> void override;

	// Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects the world
	auto AimTowardsCrosshair() const -> void;

	// Return an OUT parameter, true if hit landscape
	auto GetSightRayHitLocation(FVector& HitLocation) const -> bool;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.3333;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;

	auto GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const -> bool;
	auto GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const -> bool;
};
