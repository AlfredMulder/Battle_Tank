// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

auto UTankTrack::SetThrottle(const float Throttle) const -> void
{
	// auto const Time = GetWorld()->GetTimeSeconds();
	const auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s: throttle %f"), *Name, Throttle);

	// TODO clamp actual throttle value so player can't over-drive
	const auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	const auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
