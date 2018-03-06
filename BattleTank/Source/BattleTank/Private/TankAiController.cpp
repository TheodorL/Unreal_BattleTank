// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = GetAiControlledTank();
	if(ControlledTank == nullptr)
		UE_LOG(LogTemp, Error, TEXT("AiController not possessing a tank!"))
	else
		UE_LOG(LogTemp, Warning, TEXT("AiController possessing : %s"), *ControlledTank->GetName())
}

ATank *ATankAiController::GetAiControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


