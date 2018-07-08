// Copyright 2018 No rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put all added #includes above here

// Forward declarations
class UTankBarrel;
class UTankTurret;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Returns current health as a percentage of starting health
	UFUNCTION(BlueprintPure, Category = Health)
	float GetHealthPercent();

	// Called by the engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) override;

	FTankDelegate OnDeath;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	int32 SpawnHealth = 100;

	UPROPERTY(VisibleAnywhere)
	int32 CurrentHealth;
};
