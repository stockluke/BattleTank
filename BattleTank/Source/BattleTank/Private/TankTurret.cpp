// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::RotateTurret(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);
	auto RotationDelta = RelativeSpeed * MaxRotationRate * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = FMath::Clamp(RelativeRotation.Yaw + RotationDelta, MinRotation, MaxRotation);

	UE_LOG(LogTemp, Warning, TEXT("%.3f (%s): NewRotation= %f"), GetWorld()->GetTimeSeconds(), *GetOwner()->GetName(), NewRotation)

	SetRelativeRotation(FRotator(0.0f, NewRotation, 0.0f));
}

