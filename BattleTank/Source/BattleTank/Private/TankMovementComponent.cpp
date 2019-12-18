// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankMovementComponent.h"


auto UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) -> void
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

auto UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) -> void
{
	// No need to use Super
	const auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	const auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	const auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);

	IntendMoveForward(ForwardThrow);
	
	// UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *TankName, *MoveVelocityString);
}

auto UTankMovementComponent::IntendMoveForward(const float Throw) const -> void
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

auto UTankMovementComponent::IntendTurnRight(const float Throw) const -> void
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}
