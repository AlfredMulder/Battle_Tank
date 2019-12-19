#include "BattleTank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

auto ATank::BeginPlay() -> void
{
	Super::BeginPlay(); // Needed for BP Begin Play to run!
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

auto ATank::AimAt(const FVector HitLocation) const -> void
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

auto ATank::Fire() -> void
{
	if (!ensure(Barrel)) { return; }
	const auto bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (bIsReloaded)
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
