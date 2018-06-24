// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"

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

void UTankAimingComponent::SetBarrelReference(UTankBarrel* Barrel)
{
	this->Barrel = Barrel;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* Turret)
{
	this->Turret = Turret;
}

void UTankAimingComponent::AimAt(FVector EndLocation, float ProjectileSpeed)
{
	if (!Barrel) { return; }
	auto BarrelLocation = Barrel->GetComponentLocation();

	FVector TossVelocity = FVector(0.0f);
	auto StartLocation = Barrel->GetSocketLocation(FName("ProjectileStart"));

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

	auto AimDirection = TossVelocity.GetSafeNormal().Rotation();
	auto DeltaElevation = AimDirection - Barrel->GetForwardVector().Rotation();

	Barrel->ElevateBarrel(DeltaElevation.Pitch);
	Turret->RotateTurret(DeltaElevation.Yaw);
}