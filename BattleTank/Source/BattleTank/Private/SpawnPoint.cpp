// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine.h"
#include "SpawnPoint.h"

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
auto USpawnPoint::BeginPlay() -> void
{
	Super::BeginPlay();

	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform());
	if (!SpawnedActor) return;
	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());
}


// Called every frame
auto USpawnPoint::TickComponent(const float DeltaTime, const ELevelTick TickType,
                                FActorComponentTickFunction* ThisTickFunction) -> void
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
