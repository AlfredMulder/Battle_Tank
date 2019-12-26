// Fill out your copyright notice in the Description page of Project Settings.
#include "SprungWheel.h"
#include "SpawnPoint.h"
#include "GameFramework/Actor.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

auto UTankTrack::SetThrottle(const float Throttle) const -> void
{
	const auto CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

auto UTankTrack::DriveTrack(const float CurrentThrottle) const -> void
{
	const auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();
	const auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (auto Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

auto UTankTrack::GetWheels() const -> TArray<ASprungWheel*>
{
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (auto Child : Children)
	{
		const auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) continue;

		const auto SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) continue;

		ResultArray.Add(SprungWheel);
	}
	return ResultArray;
}
