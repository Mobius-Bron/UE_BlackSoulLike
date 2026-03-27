// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/VirgoGameplayAbility.h"
#include "VirgoEnemyGameplayAbility.generated.h"

class AVirgoEnemyCharacter;
class UEnemyCombatComponent;

/**
 * 
 */
UCLASS()
class GASTEMPLATE_API UVirgoEnemyGameplayAbility : public UVirgoGameplayAbility
{
	GENERATED_BODY()

public:
		UFUNCTION(BlueprintPure, Category = "Virgo|Ability")
		AVirgoEnemyCharacter* GetEnemyCharacterFromActorInfo();

		UFUNCTION(BlueprintPure, Category = "Virgo|Ability")
		UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<AVirgoEnemyCharacter> CachedVirgoEnemyCharacter;
	
};
