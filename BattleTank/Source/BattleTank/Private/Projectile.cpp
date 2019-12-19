#include "BattleTank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
auto AProjectile::BeginPlay() -> void
{
	Super::BeginPlay();
	
}

// Called every frame
auto AProjectile::Tick(const float DeltaTime) -> void
{
	Super::Tick( DeltaTime );

}

auto AProjectile::LaunchProjectile(const float Speed) const -> void
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
}
