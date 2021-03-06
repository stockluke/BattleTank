// Copyright 2018 No rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming status
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	Empty
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds Barrel properties and values
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Gives class reference to Barrel and Turret
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankBarrel* Barrel, UTankTurret* Turret);

	// Moves Barrel and Turret for aim solution at 'end location'
	void AimAt(FVector EndLocation);

	// Fires projectile from barrel
	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	// Determines speed of the projectile
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ProjectileSpeed = 10000; //TODO find good value

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = Firing)
	int32 GetAmmoAmount() const;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Status of the tank's firing
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState FiringState = EFiringState::Reloading;
	
private:
	bool IsBarrelMoving();

	// Sets the type of projectile
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	TSubclassOf<AProjectile> ProjectileBP;

	// Time to reload a shot in seconds
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	int32 AmmoAmount = 2;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	double LastFireTime = 0.0;
	FRotator AimDirection = FRotator(0.0f);
};
