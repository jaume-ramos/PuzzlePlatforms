// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform() {
	
	PrimaryActorTick.bCanEverTick = true;

	movingSpeed = 5.f;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay() {

	Super::BeginPlay();

	if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	// Store the initial location of the target
	GlobalStartLocation = GetActorLocation();
	// Convert local target coordinates to world coordinates
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if (ActiveTriggers > 0) {
		if (HasAuthority()) {
			FVector Location = GetActorLocation();

			float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
			float JourneyTravelled = (Location - GlobalStartLocation).Size();

			if (JourneyTravelled >= JourneyLength) {

				FVector swapTemp = GlobalStartLocation;
				GlobalStartLocation = GlobalTargetLocation;
				GlobalTargetLocation = swapTemp;
			}

			FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();

			Location += movingSpeed * DeltaTime * Direction;

			SetActorLocation(Location);
		}
	}
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0) {
		ActiveTriggers--;
	}
}
