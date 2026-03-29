// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"

#include "DataTypes/VirgoEnumTypes.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/Abilities/VirgoGameplayAbility.h"
#include "VirgoStructTypes.generated.h"

class UInputMappingContext;

USTRUCT(BlueprintType)
struct FVirgoHeroAbilitySet
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UVirgoGameplayAbility> AbilityToGrant;

	bool IsValid() const
	{
		return InputTag.IsValid() && AbilityToGrant != nullptr;
	}
};

USTRUCT(BlueprintType)
struct FVirgoHeroWeaponData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UAnimInstance> LinkedAnimLayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FVirgoHeroAbilitySet> WeaponAbilityToGrant;
};