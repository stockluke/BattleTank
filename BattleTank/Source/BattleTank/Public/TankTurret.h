// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void RotateTurret(float RelativeSpeed);

private:
	// Minimum rotation in degrees
	UPROPERTY(EditAnywhere, Category = Setup, meta = (UIMin = -180, UIMax = 180))
	float MinRotation = -180.0f;

	// Maximum rotation in degrees
	UPROPERTY(EditAnywhere, Category = Setup, meta = (UIMin = -180, UIMax = 180))
	float MaxRotation = 180.0f;

	// Maximum turret rotation rate in degrees per second
	UPROPERTY(EditAnywhere, Category = Setup, meta = (ClampMin = 0))
	float MaxRotationRate = 20.0f;
};
