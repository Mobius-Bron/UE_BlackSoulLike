// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/VirgoAttributeSet.h"
#include "GameplayEffectExtension.h"

UVirgoAttributeSet::UVirgoAttributeSet()
{
	InitMaxHealth(1.0f);
	InitCurrentHealth(1.0f);
	InitAttackPower(1.0f);
	InitDefensePower(1.0f);
}

void UVirgoAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.0f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();

		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.0f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);

		const FString DebugString = FString::Printf(
			TEXT("Damage: %f | CurrentHealth: %f"),
			DamageDone,
			NewCurrentHealth
		);

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DebugString);

		// 触发通知
		// 死亡
		if (NewCurrentHealth == 0.0f)
		{

		}
		// 血量变化
	}
}
