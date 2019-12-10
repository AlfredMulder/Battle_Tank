// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

auto ATankPlayerController::BeginPlay() -> void
{
	Super::BeginPlay();
	const auto ControlledTank = GetControlledTank();
	if(!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()))
	}
	
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"))
}


auto ATankPlayerController::GetControlledTank() const -> ATank*
{
	return Cast<ATank>(GetPawn());
}
