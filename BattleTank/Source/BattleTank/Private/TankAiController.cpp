// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"


void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
	AiTank = GetPawn();
}

void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerTank) {
		PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
		AimingComponent = AiTank->FindComponentByClass<UTankAimingComponent>();
	}
	
	if (!ensure(PlayerTank && AiTank)) return;

	MoveToActor(PlayerTank, AcceptanceRadius);
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	AimingComponent->Fire();
}

