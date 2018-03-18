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
	Locked
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

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void InitialiseAiming(UTankBarrel*  BarrelToSet, UTankTurret* TurretToSet);
	

	void AimAt(FVector AimLocation);
	
	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();


protected:

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;

	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 10000;
		
	//Points the barrel towards AimDirection
	void MoveBarrelTowards(FVector AimDirection);

	bool IsBarrelMoving() const;


	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AProjectileActor> ProjectileBlueprint;


	float ReloadTimeInSeconds = 3.0f;
	float LastFireTime = 0.0f;
	FVector OutLaunchVelocity = FVector(0);
};
