// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Public/CollisionQueryParams.h"
#include "Engine/World.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	ATank *GetControlledTank() const;
	ATank *ControlledTank =  nullptr;
	void  AimToCrosshair();
	bool  GetSightRayHitLocation(FVector &HitLocation) const;
	bool  GetLookDirection      (FVector2D CrosshairLocation, FVector &LookDirection) const;
	bool  GetLookDirectionTraceHit(FVector LookDirection, FVector &HitLocation) const;

	UPROPERTY(EditAnywhere) 
		float CrosshairLocationX =     0.5;
	
	UPROPERTY(EditAnywhere) 
		float CrosshairLocationY = 0.33333;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.0f;
};
