// Copyright 2018 No rights reserved

#include "Tank.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();	// Needed for BP's BeginPlay

	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation, ProjectileSpeed);
}

void ATank::Fire()
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
