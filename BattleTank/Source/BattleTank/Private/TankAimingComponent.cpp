// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
auto UTankAimingComponent::BeginPlay() -> void
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
auto UTankAimingComponent::TickComponent(const float DeltaTime, const ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction) -> void
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

auto UTankAimingComponent::AimAt(const FVector HitLocation) const -> void
{
	const auto OurTankName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *OurTankName, *HitLocation.ToString());
}

auto UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet) -> void
{
	Barrel = BarrelToSet;
}

