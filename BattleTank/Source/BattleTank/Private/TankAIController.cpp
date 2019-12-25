// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"
#include "TankAIController.h"
#include "Tank.h" // For death implement

auto ATankAIController::BeginPlay() -> void
{
	Super::BeginPlay();
}

auto ATankAIController::SetPawn(APawn* InPawn) -> void
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!PossessedTank) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

// Called every frame
auto ATankAIController::Tick(const float DeltaSeconds) -> void
{
	Super::Tick(DeltaSeconds);

	const auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	const auto ControlledTank = GetPawn();

	if (!(PlayerTank && ControlledTank)) { return; }

	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm

	// Aim towards the player
	const auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
}

auto ATankAIController::OnPossessedTankDeath() -> void
{
	if (!ensure(GetPawn())) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}
