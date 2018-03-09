// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"


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
	FVector OutLaunchVelocity = FVector();
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileSocket"));

	if (UGameplayStatics::SuggestProjectileVelocity(
		this, 
		OutLaunchVelocity, 
		StartLocation,
		AimLocation, 
		LaunchSpeed,
		false, 
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		MoveBarrelTowards(OutLaunchVelocity.GetSafeNormal());
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotation = AimAsRotator - BarrelRotation;
	Barrel->Elevate(5.0f);
}

