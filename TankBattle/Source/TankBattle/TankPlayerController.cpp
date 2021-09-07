// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankBattle.h"
#include "Tank.h"

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

void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	//approach the target designated by crosshair
	AimTowardsCrosshair();
	
}

void ATankPlayerController::AimTowardsCrosshair()
{

	if (!GetControlledTank())
	{
		return; //we have no tank, thus can't aim
	}

	//get world location through crosshair
	FVector HitLocation;
	//Assign intersection to hitloc
	if (GetSightRayHitLocation(HitLocation)) //Has the side-effect of setting HitLocation
	{	//if hitting landscape
		GetControlledTank()->AimAt(HitLocation);
	}


}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//find crosshair direction
	   int32 ViewportSizeX, ViewportSizeY;
	   
	   GetViewportSize(ViewportSizeX, ViewportSizeY);

	   FVector2D ScreenLocation(ViewportSizeX*CrosshairXLocation, ViewportSizeY*CrosshairYLocation);
	   FVector LookDirection;
	//deproject scrren coordinates of the crosshair into worldspace
	// 
	   if (GetLookDirection(ScreenLocation, LookDirection))
	   {
	   //linetrace along the look direction, scan for hit within defined max range
		   GetLookVectorHitLocation(LookDirection, OutHitLocation);

	   }

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);


	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * MaxRange*100;

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	))
	{
		//set hit loc
		HitLocation = HitResult.Location;
		return true;
	}
	return false;
}
