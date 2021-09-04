// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankBattle.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast <ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("TankController reports for duty"))

		auto ControlledTank = GetControlledTank();

	if (ControlledTank == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController: No Tank possessed!"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s "), *(ControlledTank->GetName()) )
	}
}
