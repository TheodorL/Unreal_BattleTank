// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"


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

	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
}

void ATankAiController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) return;

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAiController::OnThisTankDeath);
	}
}

void ATankAiController::OnThisTankDeath()
{
	if (!GetPawn()) return;

	GetPawn()->DetachFromControllerPendingDestroy();
	this->Destroy();

}

