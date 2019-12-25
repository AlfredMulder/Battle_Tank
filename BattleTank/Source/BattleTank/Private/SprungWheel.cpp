// Fill out your copyright notice in the Description page of Project Settings.

#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
	SetRootComponent(MassWheelConstraint);

	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	Mass->SetupAttachment(MassWheelConstraint);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(MassWheelConstraint);
}

// Called when the game starts or when spawned
auto ASprungWheel::BeginPlay() -> void
{
	Super::BeginPlay();

	if (GetAttachParentActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Not NULL"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NULL"))
	}
}

// Called every frame
auto ASprungWheel::Tick(const float DeltaTime) -> void
{
	Super::Tick(DeltaTime);
}
