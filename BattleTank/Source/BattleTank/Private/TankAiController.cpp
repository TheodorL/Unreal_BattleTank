// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"


void ATankAiController::BeginPlay()
{
	Super::BeginPlay();

	AiControlledTank = GetAiControlledTank();
	if (AiControlledTank == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AiController not possessing a tank!"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AiController possessing : %s"),
			*AiControlledTank->GetName())
	}

	PlayerControlledTank = GetPlayerControlledTank();
	if (PlayerControlledTank == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT( "PlayerController not possessing a tank!"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT( "AiController found PlayerController possessing: %s"),
			*PlayerControlledTank->GetName())
	}
}

ATank *ATankAiController::GetAiControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAiController::GetPlayerControlledTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


