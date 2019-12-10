// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include  "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController final : public APlayerController
{
	GENERATED_BODY()

public:
	auto GetControlledTank() const -> ATank*;

	auto BeginPlay() -> void override;
	
};
