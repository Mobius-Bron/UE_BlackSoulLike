// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/VirgoAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "VirgoGameplayTag.h"
#include "GAS_FunctionLibrary.h"

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

		UE_LOG(LogTemp, Warning, TEXT("Health: %f"), NewCurrentHealth);

		// 触发通知
		// 死亡
		if (NewCurrentHealth == 0.0f)
		{
			UGAS_FunctionLibrary::AddGameplayTagToActorIfNone(
				Data.Target.GetAvatarActor(), 
				VirgoGameplayTags::Shared_Status_Dead
			);
		}
		// 血量变化
	}
}
