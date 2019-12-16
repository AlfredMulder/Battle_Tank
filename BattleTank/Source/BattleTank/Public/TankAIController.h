// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController final : public AAIController
{
	GENERATED_BODY()

public:
	
	auto Tick(float DeltaTime) -> void override;

protected:
	
	auto BeginPlay() -> void override;

private:

	// How close can the AI tank get
	float AcceptanceRadius = 3000;
};
