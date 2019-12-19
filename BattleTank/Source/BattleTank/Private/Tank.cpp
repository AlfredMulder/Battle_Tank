#include "BattleTank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect points as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

auto ATank::SetBarrelReference(UTankBarrel* BarrelToSet) -> void
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

auto ATank::SetTurretReference(UTankTurret* TurretToSet) const -> void
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

// Called when the game starts or when spawned
auto ATank::BeginPlay() -> void
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

auto ATank::Fire() -> void
{
	const auto bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && bIsReloaded)
	{
		// Spawn a projectile at the socket location on the barrel
		const auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}
