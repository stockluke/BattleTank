// Copyright 2018 No rights reserved

#include "TankMovementComponent.h"
#include "TankTrack.h"



void UTankMovementComponent::IntentMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	//TODO prevent double input from other input
}

void UTankMovementComponent::IntentTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

	//TODO prevent double input from other input
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector AIForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	float ForwardThrow = FVector::DotProduct(AIForwardDirection, AIForwardIntention);
	float TurnThrow = FVector::CrossProduct(AIForwardDirection, AIForwardIntention).Z;

	IntentMoveForward(ForwardThrow);
	IntentTurnRight(TurnThrow);
}

void UTankMovementComponent::Initialize(UTankTrack * LeftTrack, UTankTrack * RightTrack)
{
	if(!ensure(LeftTrack && RightTrack)) { return; }
	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}
