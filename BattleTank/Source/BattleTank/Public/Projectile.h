// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	auto BeginPlay() -> void override;
	
	// Called every frame
	auto Tick(float DeltaSeconds) -> void override;

	auto LaunchProjectile(float Speed) const -> void;

private:
	UProjectileMovementComponent* ProjectileMovement = nullptr;
};
