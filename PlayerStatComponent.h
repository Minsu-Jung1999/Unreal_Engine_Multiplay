// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerStatComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPGGAMEPRACTICE_API UPlayerStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerStatComponent();

public:
	UPROPERTY(Replicated)
		float Hunger;
		
	UPROPERTY(EditAnywhere, Category = "S|PlayeerStats")
		float HungerDecrementValue;
	UPROPERTY(Replicated)
		float Thirst;

	UPROPERTY(EditAnywhere, Category = "S|PlayeerStats")
		float ThirstDecrementValue;

	FTimerHandle Timerhandle;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void HandleHungerAndThirst();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerLowerHunger(float Value);
	bool ServerLowerHunger_Validate(float Value);
	void ServerLowerHunger_Implementation(float Value);
	
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerLowerThirst(float Value);
	bool ServerLowerThirst_Validate(float Value);
	void ServerLowerThirst_Implementation(float Value);

public:
	void LowerHunger(float Value);
	void LowerThirst(float Value);
	float GetHunger();
	float GetThirst();

};
