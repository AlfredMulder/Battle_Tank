// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankBarrel.h"

auto UTankBarrel::Elevate(float RelativeSpeed) -> void
{
	// Move the barrel the right amount this frame
	// Given a max elevation speed,and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, +1.f);
	const auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	const auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	const auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
	
}
