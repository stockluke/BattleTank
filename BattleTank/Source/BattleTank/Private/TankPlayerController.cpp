// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = Cast<ATank>(GetPawn());
	UE_LOG(LogTemp, Warning, TEXT("ControlledTank Found: %s"), *ControlledTank->GetName())

	
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

