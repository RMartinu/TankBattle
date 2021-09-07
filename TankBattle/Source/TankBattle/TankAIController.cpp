// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank> (GetPawn());
}

void ATankAIController::BeginPlay()
{

    Super::BeginPlay();
    auto ControlledTank = GetControlledTank();
    auto PlayerTank = GetPlayerTank();
    UE_LOG(LogTemp, Warning, TEXT("AIController Online"))
    if (ControlledTank == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("AIController without a Tank"))
    }
    else
    {
        UE_LOG(LogTemp,Warning, TEXT("AIController got Tank: %s "), *(ControlledTank->GetName()))
    }

    if (PlayerTank == nullptr)
    {
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("AIControoler got traget: %s"), *(PlayerTank->GetName()))
    }
}

ATank* ATankAIController::GetPlayerTank() const
{
    ATank* PlayerTank = nullptr;
    auto player = GetWorld()->GetFirstPlayerController();
    if (player == nullptr)
    {
        UE_LOG(LogTemp,Error, TEXT("AIController: Didn't find Player"))
    }
    else {
        PlayerTank = Cast<ATank>(player->GetPawn());
    }
    return PlayerTank;
}

void ATankAIController::Tick(float deltaTime)
{
    Super::Tick(deltaTime);
    // TODO guard pointers!
    //approach the target designated by crosshair
    auto AimPoint = GetWorld()->GetFirstPlayerController()->GetTargetLocation(this->GetControlledTank());
    GetControlledTank()->AimAt(AimPoint);
}
