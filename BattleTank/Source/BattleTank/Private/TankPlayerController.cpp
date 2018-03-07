// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = GetControlledTank();
	if (ControlledTank == nullptr)
		UE_LOG(LogTemp, Error, TEXT("ControlledTank not found!"))
	else
		UE_LOG(LogTemp, Warning, TEXT( "Pawn : %s" ),
			*ControlledTank->GetName())
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimToCrosshair();
}

ATank *ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimToCrosshair()
{
	if (!ControlledTank) return;
	FVector HitLocation; //Out Parameter;
	if (GetSightRayHitLocation(HitLocation)) return;
		UE_LOG(LogTemp,Warning,TEXT("HitLocation : %s"),
			*HitLocation.ToString())
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	FVector2D CrosshairLocation = FVector2D(ViewPortSizeX * CrosshairLocationX, ViewPortSizeY * CrosshairLocationY);
	FVector LookDirection;
	
	if (GetLookDirection(CrosshairLocation, LookDirection))
	{
		GetLookDirectionTraceHit(LookDirection, HitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D CrosshairLocation, FVector &LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		CrosshairLocation.X, 
		CrosshairLocation.Y, 
		CameraWorldLocation, 
		LookDirection);
	
}

bool ATankPlayerController::GetLookDirectionTraceHit(FVector LookDirection, FVector & HitLocation) const
{
	FHitResult TraceHitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(GetPawn());
	if (GetWorld()->LineTraceSingleByChannel(
		TraceHitResult, 
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility,
		CollisionParameters
		))
	{
		HitLocation = TraceHitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}




