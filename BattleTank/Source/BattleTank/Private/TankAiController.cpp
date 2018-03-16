// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "Engine/World.h"
#include "Tank.h"


void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ATankAiController::Tick(float DeltaTime)
{
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ATank* AiTank = Cast<ATank>(GetPawn());
	Super::Tick(DeltaTime);
	if (PlayerTank)
	{
		MoveToActor(PlayerTank, AcceptanceRadius);


		AiTank->AimAt(PlayerTank->GetActorLocation());
		AiTank->Fire();
	}
}

