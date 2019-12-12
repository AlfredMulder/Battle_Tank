// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent final : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// TODO add SetTurretReference

	auto AimAt(FVector HitLocation, float LaunchSpeed) const ->  void;

	auto SetBarrelReference(UStaticMeshComponent* BarrelToSet) -> void;


private:
	UStaticMeshComponent* Barrel = nullptr;

	auto MoveBarrelTowards(FVector AimDirection) const -> void;
};
