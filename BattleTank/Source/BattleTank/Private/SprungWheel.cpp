// Fill out your copyright notice in the Description page of Project Settings.

#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "SprungWheel.h"
#include "Components/SphereComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
	SetRootComponent(MassWheelConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(MassWheelConstraint);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	AxleWheelConstraint->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
auto ASprungWheel::BeginPlay() -> void
{
	Super::BeginPlay();

	SetupConstraint();
}

auto ASprungWheel::SetupConstraint() const -> void
{
	if (!GetAttachParentActor()) return;
	const auto BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) return;
	MassWheelConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

// Called every frame
auto ASprungWheel::Tick(const float DeltaTime) -> void
{
	Super::Tick(DeltaTime);
}

auto ASprungWheel::AddDrivingForce(const float ForceMagnitude) const -> void
{
	Wheel->AddForce(Axle->GetForwardVector() * ForceMagnitude);
}
