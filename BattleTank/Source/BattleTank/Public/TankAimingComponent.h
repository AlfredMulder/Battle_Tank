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

	// Called every frame
	auto TickComponent(float DeltaTime, ELevelTick TickType,
	                   FActorComponentTickFunction* ThisTickFunction) -> void override;

	auto AimAt(FVector HitLocation) const ->  void;

	auto SetBarrelReference(UStaticMeshComponent* BarrelToSet) -> void;

protected:
	// Called when the game starts
	auto BeginPlay() -> void override;

private:
	UStaticMeshComponent* Barrel = nullptr;
	
};
