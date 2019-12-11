// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// No need to protect points as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
auto ATank::BeginPlay() -> void
{
	Super::BeginPlay();
	
}

auto ATank::AimAt(const FVector HitLocation) const -> void
{
	TankAimingComponent->AimAt(HitLocation);
}

auto ATank::SetBarrelReference(UStaticMeshComponent* BarrelToSet) const -> void
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

// Called every frame
auto ATank::Tick(const float DeltaTime) -> void
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
auto ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) -> void
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

