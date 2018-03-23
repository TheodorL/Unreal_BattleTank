// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAiController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAiController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
		float AcceptanceRadius = 800000.0f;


private:
	APawn * PlayerTank = nullptr;
	APawn * AiTank = nullptr;
	UTankAimingComponent *AimingComponent = nullptr;

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
		void OnThisTankDeath();
};
