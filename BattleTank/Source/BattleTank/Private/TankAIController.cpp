// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto AITank = Cast<ATank>(GetPawn());
	UE_LOG(LogTemp, Warning, TEXT("AITank Found: %s"), *AITank->GetName())
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
