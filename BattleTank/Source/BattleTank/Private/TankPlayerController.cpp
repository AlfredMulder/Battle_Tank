// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "TankPlayerController.h"


auto ATankPlayerController::BeginPlay() -> void
{
	Super::BeginPlay();
	const auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

auto ATankPlayerController::Tick(const float DeltaTime) -> void
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
}

auto ATankPlayerController::AimTowardsCrosshair() const -> void
{
	if (!GetPawn()) { return; } // e.g. if not possessing
	const auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation)) // Has "side-effect", is going to line trace
	{
		AimingComponent->AimAt(HitLocation);
	}
}

// Get world location of linetrace through crosshair, true if hits landscape
auto ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const -> bool
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	const auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that LookDirection, and see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	
	return true;
}

auto ATankPlayerController::GetLookVectorHitLocation(const FVector LookDirection, FVector& HitLocation) const -> bool
{
	FHitResult HitResult;
	const auto StartLocation = PlayerCameraManager->GetCameraLocation();
	const auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false; // Line trace didn't succeed
}

auto ATankPlayerController::GetLookDirection(const FVector2D ScreenLocation, FVector& LookDirection) const -> bool
{
	FVector CameraWorldLocation; // To be discarded
	return  DeprojectScreenPositionToWorld(
			ScreenLocation.X,
			ScreenLocation.Y, 
			CameraWorldLocation,
			LookDirection
	);
}