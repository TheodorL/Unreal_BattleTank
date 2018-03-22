// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

// Forward declaration
class UTankBarrel; 
class UTankTurret;
class AProjectileActor;

//Holds barrels properties and Elevate
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	//used in BP to initialise the barrel and turret pointers
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void InitialiseAiming(UTankBarrel*  BarrelToSet, UTankTurret* TurretToSet);
	
	//calls methods further down dependecy map in order to move turret and barrel
	void AimAt(FVector AimLocation);
	
	//calls projectile method further down dependency map using proper parameter
	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

	//returns the firing state of the current object
	EFiringState GetFiringState() const;

protected:

	//the default firing state
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 RoundsLeft = 3;

private:

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 10000;

	//the time between shots
	UPROPERTY(EditDefaultsOnly)
		float ReloadTimeInSeconds = 3.0f;
		
	//Points the barrel and the turret towards AimDirection
	void MoveTurretAndBarrelTowards(FVector AimDirection);

	//returns true if the barrel is currently moving
	bool IsBarrelMoving() const;

	//the projectile that is spawned when the Fire() method is called, editable in BP
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectileActor> ProjectileBlueprint;

	float LastFireTime = 0.0f;
	FVector OutLaunchVelocity = FVector(0);
};
