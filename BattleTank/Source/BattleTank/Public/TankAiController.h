// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAiController.generated.h"

class ATank;
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

private:
	ATank *AiTank     =  nullptr;
	ATank *PlayerTank =  nullptr;

	float AcceptanceRadius = 400.0f;
	
};
