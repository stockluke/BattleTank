// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
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
	if (!Barrel) { return; }
	UE_LOG(LogTemp, Warning, TEXT("%.3f: Fire!"), GetWorld()->GetTimeSeconds())

	auto ProjectileStart = Barrel->GetSocketTransform(FName("ProjectileStart"));
	GetWorld()->SpawnActor<AProjectile>(ProjectileBP, ProjectileStart);
}
