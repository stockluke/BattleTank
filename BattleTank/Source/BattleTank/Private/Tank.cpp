// Copyright 2018 No rights reserved

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::GetHealthPercent()
{
	
	float HealthPercent = (float)CurrentHealth / (float)SpawnHealth;

	return HealthPercent;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	int32 DamageToApply = (int32)DamageAmount;
	DamageToApply = FMath::Clamp<int32>(DamageToApply, 0.0f, CurrentHealth);
	CurrentHealth -= DamageToApply;

	UE_LOG(LogTemp, Warning, TEXT("Damage: %i"), DamageToApply) 

	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}

	return DamageToApply;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();	// Needed for BP's BeginPlay
	CurrentHealth = SpawnHealth;
}


