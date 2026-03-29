// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/HeroCombatComponent.h"
#include "Components/Combat/PawnCombatComponent.h"

#include "Items/Weapons/VirgoHeroWeapon.h"

AVirgoHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag WeaponTag) const
{
	AWeaponBase* FoundWeapon = GetCharacterCarriedWeaponByTag(WeaponTag);

	AVirgoHeroWeapon* FoundHeroWeapon = Cast<AVirgoHeroWeapon>(FoundWeapon);

	return FoundHeroWeapon;
}

AVirgoHeroWeapon* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	return GetHeroCarriedWeaponByTag(CurrentEquippedWeaponTag);
}
