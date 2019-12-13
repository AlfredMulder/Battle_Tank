// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))//, HideCategories = ("Collision"))
class BATTLETANK_API UTankTurret final : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max downward speed, and +1 is max movement
	auto Rotate(float RelativeSpeed) -> void;
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 25; // Sensible Default
};
