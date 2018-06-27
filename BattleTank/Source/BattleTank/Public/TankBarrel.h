// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void ElevateBarrel(float RelativeSpeed);
	
private:
	// Minimum elevation in degrees
	UPROPERTY(EditDefaultsOnly, Category = Setup, meta = (UIMin = -90, UIMax = 90))
	float MinElevation = 0.0f;

	// Maximum elevation in degrees
	UPROPERTY(EditDefaultsOnly, Category = Setup, meta = (UIMin = -90, UIMax = 90))
	float MaxElevation = 40.0f;

	// Maximum barrel elevation rate in degrees per second
	UPROPERTY(EditDefaultsOnly, Category = Setup, meta = (ClampMin = 0))
	float MaxElevationRate = 10.0f;
};
