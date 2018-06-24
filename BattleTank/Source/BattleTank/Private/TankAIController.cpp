// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetControlledTank();
	UE_LOG(LogTemp, Warning, TEXT("AITank Found: %s"), *PlayerTank->GetName())
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		AimTowardsPlayer(PlayerTank);
		MoveTowardsPlayer(PlayerTank);
		//Fire if ready
	}
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::AimTowardsPlayer(ATank* PlayerTank) const
{	
	GetControlledTank()->AimAt(PlayerTank->GetActorLocation());
}

void ATankAIController::MoveTowardsPlayer(ATank* PlayerTank) const
{

}
