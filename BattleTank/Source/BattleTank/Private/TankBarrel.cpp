// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"


void UTankBarrel::Elevate(float DegreesPerSecond)
{
	FString degrees = FString::SanitizeFloat(DegreesPerSecond);
	UE_LOG(LogTemp, Warning, TEXT("Elevation speed : %s"), *degrees)
}




