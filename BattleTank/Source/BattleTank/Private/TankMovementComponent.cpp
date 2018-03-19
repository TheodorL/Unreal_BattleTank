// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::InitialiseMovement(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack) || !ensure(RightTrack)) return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendMoveSideways(float Throw)
{
	if (!ensure(LeftTrack) || !ensure(RightTrack)) return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed)
{
	FVector AiCurrentDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AiPathDirection = MoveVelocity.GetSafeNormal();
	float ForwardRelativeThrottle = FVector::DotProduct(AiCurrentDirection, AiPathDirection);
	float SidewaysRelativeThrottle = FVector::CrossProduct(AiCurrentDirection, AiPathDirection).Z;
	IntendMoveForward(ForwardRelativeThrottle);
	IntendMoveSideways(SidewaysRelativeThrottle);
}


