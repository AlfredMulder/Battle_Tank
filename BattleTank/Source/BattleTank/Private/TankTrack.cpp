// Fill out your copyright notice in the Description page of Project Settings.
#include "GameFramework/Actor.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

auto UTankTrack::TickComponent(const float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction) -> void
{
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	// Work-out the required acceleration this frame to correct
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	// Calculate and apply sideways (F = m a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two tracks
	TankRoot->AddForce(CorrectionForce);
}

auto UTankTrack::SetThrottle(const float Throttle) const -> void
{
	const auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	const auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);	
}
