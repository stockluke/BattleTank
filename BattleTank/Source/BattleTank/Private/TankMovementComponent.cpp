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
	UE_LOG(LogTemp, Warning, TEXT("%.3f: Throw %f"), GetWorld()->GetTimeSeconds(), Throw)

	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

	//TODO prevent double input from other input
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
