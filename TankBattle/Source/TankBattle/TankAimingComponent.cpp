// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector TargetLocation, float MuzzleVelocity)
{
	if (Barrel != nullptr) {
		FVector FiringVector;
		FVector StartLocation = Barrel->GetSocketLocation(FName("Muzzle"));
		TArray<AActor*> ignored;
		//ask for trajectory calculation
		bool hasValidFiringSolution = UGameplayStatics::SuggestProjectileVelocity(this,
			FiringVector,
			StartLocation,
			TargetLocation,
			MuzzleVelocity,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace,
			FCollisionResponseParams::DefaultResponseParam,
			ignored,
			true //TODO disabple hit tracers
		);

		if(hasValidFiringSolution)
		{
			//we can hit the target
			auto AimDirection = FiringVector.GetSafeNormal();
			//UE_LOG(LogTemp, Warning, TEXT("Tank is aiming: %s "), *AimDirection.ToString())
			MoveBarrelTowards(AimDirection);
		}
		else
		{
			//nojoy
			UE_LOG(LogTemp, Warning, TEXT("Cannot hit target"))
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("To Short a Barrel!"))
	}
}

bool UTankAimingComponent::MoveBarrelTowards(FVector FiringSolution)
{
	//evaluate difference between current and intended barrel alignment
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = FiringSolution.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//move barrel to reduce difference within max elevation speed and frame time
	Barrel->ElevateBarrel(DeltaRotator.Pitch); //TODO get rid of magic numbers
	UE_LOG(LogTemp, Warning, TEXT("Aiming at: %s"), *AimAsRotator.ToString())
	return false;
}

