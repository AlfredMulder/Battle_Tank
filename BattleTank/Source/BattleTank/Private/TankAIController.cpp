// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"
#include "TankAIController.h"

auto ATankAIController::BeginPlay() -> void
{
	Super::BeginPlay();
}

// Called every frame
auto ATankAIController::Tick(const float DeltaSeconds) -> void
{
	Super::Tick(DeltaSeconds);

	const auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	const auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	
	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm
	const auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	// Aim towards the player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	AimingComponent->Fire(); // TODO limit firing rate
	
}