// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::TurretRotate(float rotationRate)
{
	auto relativeRate = FMath::Clamp<float>(rotationRate, -1.f, 1.f);
	auto rotationChange = relativeRate * this->maxYawRate * GetWorld()->DeltaTimeSeconds;
	auto newRotation = GetRelativeRotation().Yaw + rotationChange;
	UE_LOG(LogTemp, Warning, TEXT("Rotating by: %f"), newRotation)
	SetRelativeRotation(FRotator(0,newRotation,0));
}