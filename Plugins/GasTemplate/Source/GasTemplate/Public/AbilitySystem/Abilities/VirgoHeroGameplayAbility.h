// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/VirgoGameplayAbility.h"
#include "VirgoHeroGameplayAbility.generated.h"

class AVirgoHeroCharacter;
class AVirgoController;
class UHeroCombatComponent;

/**
 * 
 */
UCLASS()
class GASTEMPLATE_API UVirgoHeroGameplayAbility : public UVirgoGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Virgo|Ability")
	AVirgoHeroCharacter* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Virgo|Ability")
	AVirgoController* GetHeroControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Virgo|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<AVirgoHeroCharacter> CachedVirgoHeroCharacter;
	TWeakObjectPtr<AVirgoController> CachedVirgoController;
};
