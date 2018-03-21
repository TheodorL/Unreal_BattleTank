// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "ProjectileActor.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (RoundsLeft <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(Barrel)) return false;
	FVector BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(OutLaunchVelocity.GetSafeNormal(), 0.01f);
}



void UTankAimingComponent::InitialiseAiming(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector AimLocation)
{
	if (!ensure(Barrel) || !ensure(Turret)) return;
	OutLaunchVelocity;
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
		MoveTurretAndBarrelTowards(OutLaunchVelocity.GetSafeNormal());
	}
}


void UTankAimingComponent::MoveTurretAndBarrelTowards(FVector AimDirection)
{
	float BarrelPitch = Barrel->GetForwardVector().Rotation().Pitch;
	float TurretYaw = Turret->GetForwardVector().Rotation().Yaw + 180;
	float AimPitch = AimDirection.Rotation().Pitch;
	float AimYaw = AimDirection.Rotation().Yaw + 180;
	float DeltaPitch = AimPitch - BarrelPitch;
	float DeltaYaw = AimYaw - TurretYaw;
	if (DeltaYaw > 180)
	{
		DeltaYaw = 360 - DeltaYaw;
		DeltaYaw = -DeltaYaw;
	}
	if (DeltaYaw < -180)
	{
		DeltaYaw = -DeltaYaw;
		DeltaYaw = 360 - DeltaYaw;
	}

	Barrel->Elevate(DeltaPitch);
	Turret->YawTurret(DeltaYaw);
}

void UTankAimingComponent::Fire()
{
	
	if (FiringState == EFiringState::Aiming || FiringState == EFiringState::Locked)
	{
		if (!ensure(Barrel)) return;
		if (!ensure(ProjectileBlueprint))return;
		auto Projectile = GetWorld()->SpawnActor<AProjectileActor>(
										ProjectileBlueprint,
										Barrel->GetSocketLocation(FName("ProjectileSocket")),
										Barrel->GetSocketRotation(FName("ProjectileSocket")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		RoundsLeft--;
	}

}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}


