// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = GetControlledTank();
	if (ControlledTank == nullptr)
		UE_LOG(LogTemp, Error, TEXT("ControlledTank not found!"))
	else
		UE_LOG(LogTemp, Warning, TEXT("Pawn : %s"), *ControlledTank->GetName())
}

ATank *ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}




