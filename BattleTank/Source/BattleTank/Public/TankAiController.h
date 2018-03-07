// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Tank.h"
#include "AIController.h"
#include "TankAiController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAiController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	ATank *GetAiControlledTank()     const;
	ATank *GetPlayerControlledTank() const;
	ATank *AiControlledTank     =  nullptr;
	ATank *PlayerControlledTank =  nullptr;
	
};
