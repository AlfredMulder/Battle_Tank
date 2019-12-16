// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"

auto UTankMovementComponent::IntendMoveForward(float Throw) -> void
{
	// auto const Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), Throw);
}
