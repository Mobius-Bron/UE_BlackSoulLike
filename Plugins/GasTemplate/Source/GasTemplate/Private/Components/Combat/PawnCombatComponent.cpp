// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponent.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag WeaponTag, AWeaponBase* SpwanWeapon, bool RegisterAsEquippedWeapon)
{
	if (WeaponTag.IsValid()) { return; }
	if (CharacterCarriedWeaponMap.Contains(WeaponTag)) { return; }

	CharacterCarriedWeaponMap.Emplace(WeaponTag, SpwanWeapon);

	if (RegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = WeaponTag;
	}
}

void UPawnCombatComponent::UnregisterAndDestoryWeapon(FGameplayTag WeaponTag)
{
	if (AWeaponBase* WeaponToDestroy = GetCharacterCarriedWeaponByTag(WeaponTag))
	{
		CharacterCarriedWeaponMap.Remove(WeaponTag);

		if (CurrentEquippedWeaponTag == WeaponTag)
		{
			CurrentEquippedWeaponTag = FGameplayTag();
		}

		WeaponToDestroy->Destroy();
	}
}

AWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag WeaponTag) const
{
	if (WeaponTag.IsValid()) { return nullptr; }
	if (!CharacterCarriedWeaponMap.Contains(WeaponTag)) { return nullptr; }

	if (AWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(WeaponTag))
	{
		return *FoundWeapon;
	}

	return nullptr;
}

AWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}
