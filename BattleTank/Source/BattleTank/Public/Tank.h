// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank final : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called by the engine when actor damage is dealt
	auto TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	                AActor* DamageCauser) -> float override;

	auto BeginPlay() -> void override;

	FTankDelegate OnDeath;

protected:
	// Return current health as a percentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent();
	
private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth; // Initialized in BeginPlay
};
