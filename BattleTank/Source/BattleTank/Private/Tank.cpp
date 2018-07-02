// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protected as added at costruction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, ProjectileSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* Component)
{
	TankAimingComponent->SetBarrelReference(Component);
	Barrel = Component;
}

void ATank::SetTurretReference(UTankTurret* Component)
{
	TankAimingComponent->SetTurretReference(Component);
}

void ATank::Fire()
{
	bool bIsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTime;
	if (!Barrel) { return; }

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
