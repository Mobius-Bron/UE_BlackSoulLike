// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/VirgoHeroWeapon.h"

void AVirgoHeroWeapon::AssignGrantedHeroAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InAbilitySpecHandles)
{
	GrantedHeroAbilitySpecHandles = InAbilitySpecHandles;
}

TArray<FGameplayAbilitySpecHandle> AVirgoHeroWeapon::GetGrantedHeroAbilitySpecHandles()
{
	return GrantedHeroAbilitySpecHandles;
}
