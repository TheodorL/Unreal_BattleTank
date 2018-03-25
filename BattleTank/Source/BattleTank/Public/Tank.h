// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	//The number of AiControllers currently present in the scene
	static int32 NoOfAiTanks;

	static void IncreaseAiTankCount();
	static void DecreaseAiTankCount();

	//Returns NoOfAiTanks
	UFUNCTION(BlueprintCallable, Category = "Ai")
		int32 GetAiTankNo() const;

	//return current health as a float between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	FTankDelegate OnDeath;

	~ATank();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 CurrentHealth = StartingHealth;
};
