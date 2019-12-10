// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	auto BeginPlay() -> void override;

public:	
	// Called every frame
	auto Tick(float DeltaTime) -> void override;

	// Called to bind functionality to input
	auto SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) -> void override;

};
