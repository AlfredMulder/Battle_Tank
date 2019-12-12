// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect points as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

auto ATank::SetBarrelReference(UTankBarrel* BarrelToSet) const -> void
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

auto ATank::SetTurretReference(UTankTurret* TurretToSet) const -> void
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
auto ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent) -> void
{
	Super::SetupPlayerInputComponent(InputComponent);

}

auto ATank::AimAt(const FVector HitLocation) const -> void
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

