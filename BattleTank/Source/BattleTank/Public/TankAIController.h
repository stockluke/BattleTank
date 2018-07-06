// Copyright 2018 No rights reserved

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	void BeginPlay() override;

	void Tick(float DeltaTime) override;
	
protected:
	//Value to how close AI can get to player
	UPROPERTY(EditDefaultsOnly, Category = Setup, meta = (ClampMin = 0))
	float AcceptanceRadius = 8000.0f;
};
