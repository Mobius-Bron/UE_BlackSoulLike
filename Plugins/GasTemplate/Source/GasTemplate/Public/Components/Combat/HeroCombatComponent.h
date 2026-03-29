// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "HeroCombatComponent.generated.h"

class AVirgoHeroWeapon;

/**
 * 
 */
UCLASS()
class GASTEMPLATE_API UHeroCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Virgo|Combat")
	AVirgoHeroWeapon* GetHeroCarriedWeaponByTag(FGameplayTag WeaponTag) const;

	UFUNCTION(BlueprintCallable, Category = "Virgo|Combat")
	AVirgoHeroWeapon* GetHeroCurrentEquippedWeapon() const;
};
