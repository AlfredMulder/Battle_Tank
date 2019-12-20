// Fill out your copyright notice in the Description page of Project Settings.
#include "GameFramework/Actor.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

auto UTankTrack::BeginPlay() -> void
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

auto UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) -> void
{
	// Drive the tracks
	DriveTrack();
	
	// Apply sideways force
	ApplySidewaysForce();
	
	// Reset throttle
	CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce()
{
	const auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	// Work-out the required acceleration this frame to correct
	const auto DeltaTime = GetWorld()->GetDeltaSeconds();
	const auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	// Calculate and apply sideways (F = m a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	const auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::DriveTrack() const
{
	const auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	const auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

auto UTankTrack::SetThrottle(const float Throttle) -> void

{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}
