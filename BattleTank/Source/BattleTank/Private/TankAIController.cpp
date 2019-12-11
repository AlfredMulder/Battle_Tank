// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
#include "TankAIController.h"

auto ATankAIController::BeginPlay() -> void
{
	Super::BeginPlay();
	const auto PlayerTank = GetPlayerTank();
	if(!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController can't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found player tank: %s"), *(PlayerTank->GetName()));
	}
	
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
}

auto ATankAIController::Tick(const float DeltaTime) -> void
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		// TODO Move towards to player
		
		// Aim towards the player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
		
		// Fire if ready
	}
}

auto ATankAIController::GetControlledTank() const -> ATank*
{
	return Cast<ATank>(GetPawn());
}

auto ATankAIController::GetPlayerTank() const -> ATank*
{
	const auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)
	{
		return nullptr;
	}
	return Cast<ATank>(PlayerPawn);
}