// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUp/DataAsset_StartUpDataBase.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/Abilities/VirgoGameplayAbility.h"
#include "DataAsset_HeroStartUpData.generated.h"

USTRUCT(BlueprintType)
struct FVirgoHeroAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UVirgoGameplayAbility> AbilityToGrant;
};

/**
 * 
 */
UCLASS()
class GASTEMPLATE_API UDataAsset_HeroStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()
	
};
