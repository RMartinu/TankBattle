// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::ElevateBarrel(float RelativeSpeed)
{
	float ElevationSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	auto ElevationChange = MaxDegreesPerSecond * ElevationSpeed*GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = GetRelativeRotation().Pitch + ElevationChange;
	float NewElevation =FMath::Clamp(RawNewElevation, MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(NewElevation,0,0));
}