#include "TankTrack.h"
#include "TankMovementComponent.h"

auto UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) -> void
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

auto UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) -> void
{
	// No need to call Super as we're replacing the functionality

	const auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	const auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	const auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	const auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);
}

auto UTankMovementComponent::IntendMoveForward(const float Throw) const -> void
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

auto UTankMovementComponent::IntendTurnRight(const float Throw) const -> void
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}
