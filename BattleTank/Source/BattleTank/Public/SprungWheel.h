// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel final : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASprungWheel();

	// Called every frame
	auto Tick(float DeltaTime) -> void override;


protected:
	// Called when the game starts or when spawned
	auto BeginPlay() -> void override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Mass = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* MassWheelConstraint = nullptr;
};
