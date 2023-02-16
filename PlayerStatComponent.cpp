// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatComponent.h"
#include "Net/UnrealNetWork.h"
#include "TimerManager.h"
#include "Engine.h"

// Sets default values for this component's properties
UPlayerStatComponent::UPlayerStatComponent()
{
	Hunger = 100.f;
	HungerDecrementValue = 0.3f;
	Thirst = 100.f;
	ThirstDecrementValue = 0.5f;
	
}


// Called when the game starts
void UPlayerStatComponent::BeginPlay()
{
	Super::BeginPlay();
	SetIsReplicated(true);
	GetWorld()->GetTimerManager().SetTimer(Timerhandle, this, &UPlayerStatComponent::HandleHungerAndThirst, 3.0f, true);
}

void UPlayerStatComponent::HandleHungerAndThirst()
{
	LowerHunger(HungerDecrementValue);
	LowerThirst(ThirstDecrementValue);
}


void UPlayerStatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPlayerStatComponent, Hunger);
	DOREPLIFETIME(UPlayerStatComponent, Thirst);
}


void UPlayerStatComponent::LowerHunger(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerLowerHunger(Value);
	}
	else
	{
		Hunger -= Value;
	}
}

void UPlayerStatComponent::LowerThirst(float Value)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerLowerThirst(Value);

	}
	else
	{
		Thirst -= Value;
	}

}



#pragma region Server_Hunger
bool UPlayerStatComponent::ServerLowerHunger_Validate(float Value)
{
	return false;
}
void UPlayerStatComponent::ServerLowerHunger(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{

	}
	else
	{
		Hunger -= Value;
	}
}


void UPlayerStatComponent::ServerLowerHunger_Implementation(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		LowerHunger(Value);
	}
	
}

#pragma endregion


#pragma region Server_Thirst
void UPlayerStatComponent::ServerLowerThirst(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{

	}
	else
	{
		Hunger -= Value;
	}
}

bool UPlayerStatComponent::ServerLowerThirst_Validate(float Value)
{
	return false;
}

void UPlayerStatComponent::ServerLowerThirst_Implementation(float Value)
{
}

#pragma endregion

float UPlayerStatComponent::GetHunger()
{
	return Hunger;
}
float UPlayerStatComponent::GetThirst()
{
	return Thirst;
}
