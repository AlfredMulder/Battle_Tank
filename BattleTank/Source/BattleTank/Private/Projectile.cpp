#include "Components/PrimitiveComponent.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
    // const FAttachmentTransformRules Rules(EAttachmentRule::KeepRelative, false);
    LaunchBlast->SetupAttachment(CollisionMesh);
	// LaunchBlast->AttachTo(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
auto AProjectile::BeginPlay() -> void
{
	Super::BeginPlay();
}

// Called every frame
auto AProjectile::Tick(const float DeltaSeconds) -> void
{
	Super::Tick( DeltaSeconds );
}

auto AProjectile::LaunchProjectile(const float Speed) const -> void
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
}
