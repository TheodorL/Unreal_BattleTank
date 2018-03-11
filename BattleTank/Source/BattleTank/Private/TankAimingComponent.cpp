// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts


void UTankAimingComponent::AimAt(FVector AimLocation, float LaunchSpeed)
{
	if (!Barrel) return;
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileSocket"));

	if (UGameplayStatics::SuggestProjectileVelocity(
		this, 
		OutLaunchVelocity, 
		StartLocation,
		AimLocation, 
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		MoveBarrelTowards(OutLaunchVelocity.GetSafeNormal());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not solve aim!"))
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	if (!BarrelToSet) return;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	if (!TurretToSet) return;
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	float BarrelPitch = Barrel->GetForwardVector().Rotation().Pitch;
	float TurretYaw = Turret->GetForwardVector().Rotation().Yaw;
	float AimPitch = AimDirection.Rotation().Pitch;
	float AimYaw = AimDirection.Rotation().Yaw;
	float DeltaPitch = AimPitch - BarrelPitch;
	float DeltaYaw = AimYaw - TurretYaw;
	
	
	Barrel->Elevate(DeltaPitch);
	Turret->YawTurret(DeltaYaw);
}

