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

	UTankTrack();

	virtual void BeginPlay() override;

	void ApplySidewaysForce();

	float CurrentThrottle = 0.0f;

	
	
public:
	UFUNCTION(BlueprintCallable)
		void SetThrottle(float Throttle);

	//used to add fake friction
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	//adds a force vector to the current track
	void DriveTrack();

	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 400000.0f;



};
