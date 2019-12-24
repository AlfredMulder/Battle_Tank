// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController final : public AAIController
{
	GENERATED_BODY()

protected:
	// How close can the AI tank get
	UPROPERTY(EditDefaultsOnly, Category = "Setup") // Consider EditDefaultsOnly
	float AcceptanceRadius = 8000;
	
private:
	auto BeginPlay() -> void override;

	auto SetPawn(APawn* InPawn) -> void override;

	auto Tick(float DeltaSeconds) -> void override;

	UFUNCTION()
	void OnPossessedTankDeath();
};
