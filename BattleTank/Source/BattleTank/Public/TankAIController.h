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
	auto GetControlledTank() const -> ATank*;
	auto GetPlayerTank() const -> ATank*;
};
