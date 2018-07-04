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
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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

	FRotator AimDirection = TossVelocity.GetSafeNormal().Rotation();
	FRotator DeltaElevation = AimDirection - Barrel->GetForwardVector().Rotation();

	Barrel->ElevateBarrel(DeltaElevation.Pitch);
	Turret->RotateTurret(DeltaElevation.Yaw);
}

void UTankAimingComponent::Fire()
{
	bool bIsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTime;
	if (!ensure(Barrel)) { return; }

	if (bIsReloaded)
	{
		auto ProjectileStart = Barrel->GetSocketTransform(FName("ProjectileStart"));
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, ProjectileStart);
		if (Projectile)
		{
			Projectile->LaunchProjectile(ProjectileSpeed);
			LastFireTime = GetWorld()->GetTimeSeconds();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("The BP_Tank's projectile is not set"))
		}
	}

}