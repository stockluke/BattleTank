// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"



void UTankMovementComponent::IntentMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	//TODO prevent double input from other input
}

void UTankMovementComponent::IntentTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
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

	UE_LOG(LogTemp, Warning, TEXT("%.3f: CrossProduct %f"), GetWorld()->GetTimeSeconds(), TurnThrow)
}

void UTankMovementComponent::Initialize(UTankTrack * LeftTrack, UTankTrack * RightTrack)
{
	if(!LeftTrack || !RightTrack)
	{
		UE_LOG(LogTemp, Warning, TEXT("Left or Right Track not set in UTankMovementComponent"))
		return;
	}
	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}
