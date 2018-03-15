// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

	//Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 400000.0f;

public:
	UFUNCTION(BlueprintCallable)
		void SetThrottle(float Throttle);

};