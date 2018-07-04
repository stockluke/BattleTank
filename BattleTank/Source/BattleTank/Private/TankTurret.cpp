// Copyright 2018 No rights reserved

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::RotateTurret(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);
	auto RotationDelta = RelativeSpeed * MaxRotationRate * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationDelta;

	SetRelativeRotation(FRotator(0.0f, NewRotation, 0.0f));
}

