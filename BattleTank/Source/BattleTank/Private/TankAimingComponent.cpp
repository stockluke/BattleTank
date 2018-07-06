// Copyright 2018 No rights reserved

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = GetWorld()->GetTimeSeconds();
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (AmmoAmount < 1)
	{
		FiringState = EFiringState::Empty;
	}
	else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTime)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::Initialize(UTankBarrel * Barrel, UTankTurret * Turret)
{
	ensure(Barrel && Turret);
	this->Barrel = Barrel;
	this->Turret = Turret;
}

void UTankAimingComponent::AimAt(FVector EndLocation)
{
	if (!ensure(Barrel && Turret)) { return; }
	FVector BarrelLocation = Barrel->GetComponentLocation();

	FVector TossVelocity = FVector(0.0f);
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileStart"));

	bool bIsValidTossVelocity = UGameplayStatics::SuggestProjectileVelocity(
		this,
		TossVelocity,
		StartLocation,
		EndLocation,
		ProjectileSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (!bIsValidTossVelocity) { 
		UE_LOG(LogTemp, Warning, TEXT("%.3f (%s): No aim solution"), GetWorld()->GetTimeSeconds(), *GetOwner()->GetName())
		return; 
	}

	AimDirection = TossVelocity.GetSafeNormal().Rotation();
	FRotator DeltaRotator = AimDirection - Barrel->GetForwardVector().Rotation();
	
	Barrel->ElevateBarrel(DeltaRotator.Pitch);
	if (DeltaRotator.Yaw < 180 && DeltaRotator.Yaw > -180)
	{
		Turret->RotateTurret(DeltaRotator.Yaw);
	}
	else
	{
		Turret->RotateTurret(-DeltaRotator.Yaw);
	}
	
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBP)) { return; }

	if (FiringState != EFiringState::Reloading && FiringState != EFiringState::Empty)
	{
		auto ProjectileStart = Barrel->GetSocketTransform(FName("ProjectileStart"));
		auto ProjectileActor = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, ProjectileStart);

		ProjectileActor->LaunchProjectile(ProjectileSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();

		AmmoAmount -= 1;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

uint8 UTankAimingComponent::GetAmmoAmount() const
{
	return AmmoAmount;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	return !Barrel->GetForwardVector().Equals(AimDirection.Vector(), 0.01);
}