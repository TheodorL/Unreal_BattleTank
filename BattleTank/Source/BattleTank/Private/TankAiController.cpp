// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "Engine/World.h"
#include "Tank.h"


void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ATank* AiTank = Cast<ATank>(GetPawn());
	
}

void ATankAiController::Tick(float DeltaTime)
{
	

	Super::Tick(DeltaTime);
	if (PlayerTank)
	{
		AiTank->AimAt(PlayerTank->GetActorLocation());

		AiTank->Fire();
	}
}

