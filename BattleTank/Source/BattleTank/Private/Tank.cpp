// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

int32 ATank::NoOfAiTanks = 0;

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth/(float)StartingHealth;
}

void ATank::BeginPlay()
{
	Super::BeginPlay(); // call the blueprints begin play after executing code inside the cpp begin play
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(Damage);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if(CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}



	return 0.0f;
}

void ATank::IncreaseAiTankCount()
{
	NoOfAiTanks++;
}

void ATank::DecreaseAiTankCount()
{
	NoOfAiTanks--;
}

int32 ATank::GetAiTankNo() const
{
	return NoOfAiTanks;
}

ATank::~ATank()
{
	NoOfAiTanks = 0;
}




