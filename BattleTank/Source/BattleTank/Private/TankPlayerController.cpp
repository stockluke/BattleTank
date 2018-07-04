// Copyright 2018 No rights reserved

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString())
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation not found"))
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//find crosshair location on screen
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto CrosshairPosition = FVector2D(ViewportSizeX * CrosshairXScreenLocation, ViewportSizeY * CrosshairYScreenLocation);
	
	//find crosshair direction to landscape
	FVector WorldLocation, CrosshairDirection;
	if (DeprojectScreenPositionToWorld(CrosshairPosition.X, CrosshairPosition.Y, WorldLocation, CrosshairDirection))
	{
		GetLookVectorHitLocation(CrosshairDirection, OutHitLocation);
	}
	
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	bool bIsHitResult = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	);

	if (bIsHitResult)
	{
		HitLocation = HitResult.Location;
	}
	else
	{
		HitLocation = FVector(0.0);
	}

	return bIsHitResult;
}
