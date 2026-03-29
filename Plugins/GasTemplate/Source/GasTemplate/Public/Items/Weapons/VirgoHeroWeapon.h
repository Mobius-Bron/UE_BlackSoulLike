// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/WeaponBase.h"

#include "DataTypes/VirgoStructTypes.h"
#include "VirgoHeroWeapon.generated.h"

/**
 * 
 */
UCLASS()
class GASTEMPLATE_API AVirgoHeroWeapon : public AWeaponBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AssignGrantedHeroAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InAbilitySpecHandles);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedHeroAbilitySpecHandles();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	FVirgoHeroWeaponData WeaponData;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TArray<FGameplayAbilitySpecHandle> GrantedHeroAbilitySpecHandles;
};
