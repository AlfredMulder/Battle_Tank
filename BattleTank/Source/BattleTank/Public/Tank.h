// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank final : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called every frame
	auto Tick(float DeltaTime) -> void override;

	// Called to bind functionality to input
	auto SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) -> void override;

	auto AimAt(FVector HitLocation) const -> void;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UStaticMeshComponent* BarrelToSet) const;

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

	// Called when the game starts or when spawned
	auto BeginPlay() -> void override;
	
};
