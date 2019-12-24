#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

auto ATank::TakeDamage(const float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                       AActor* DamageCauser) -> float
{
	const auto DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	const auto DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}
	return DamageToApply;
}

auto ATank::GetHealthPercent() -> float
{
	return static_cast<float>(CurrentHealth) / static_cast<float>(StartingHealth);
}
