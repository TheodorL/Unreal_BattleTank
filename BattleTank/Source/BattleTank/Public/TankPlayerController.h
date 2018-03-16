// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank *GetControlledTank() const;


private:
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
