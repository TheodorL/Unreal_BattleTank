// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Runtime/Engine/Public/CollisionQueryParams.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if(ensure(AimingComponent))
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimToCrosshair();
}

void ATankPlayerController::AimToCrosshair()
{
	if (!ensure(AimingComponent)) return;
	FVector HitLocation; //Out Parameter;
	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
	}
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	FVector2D CrosshairLocation = FVector2D(ViewPortSizeX * CrosshairLocationX, ViewPortSizeY * CrosshairLocationY);
	FVector LookDirection;
	
	if (GetLookDirection(CrosshairLocation, LookDirection))
	{
		
		return GetLookDirectionTraceHit(LookDirection, HitLocation);
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




