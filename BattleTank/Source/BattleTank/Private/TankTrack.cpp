// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

auto UTankTrack::SetThrottle(const float Throttle) const -> void
{
	// TODO clamp actual throttle value so player can't over-drive
	const auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	const auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
