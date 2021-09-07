// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //this must be the last include!
class ATank;
/**
 * 
 */
UCLASS()
class TANKBATTLE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 1 / 3.f;

	UPROPERTY(EditAnywhere)
		int MaxRange = 10000;

	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

	//Aim the Barrel twoards the intersection of Crosshair and World
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector & OutHitLocation)const;
	bool GetLookDirection(FVector2D Screenlocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation)const;
};
