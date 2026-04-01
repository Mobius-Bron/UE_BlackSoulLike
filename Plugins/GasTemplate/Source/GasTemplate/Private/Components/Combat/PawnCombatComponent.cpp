// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponent.h"
#include "Components/BoxComponent.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag WeaponTag, AWeaponBase* SpwanWeapon, bool RegisterAsEquippedWeapon)
{
	if (!WeaponTag.IsValid())
	{
		UE_LOG(LogTemp, Display, TEXT("Register WeaponTag is nullptr"));
		return; 
	}
	if (CharacterCarriedWeaponMap.Contains(WeaponTag))
	{
		UE_LOG(LogTemp, Display, TEXT("Register WeaponTag %s is already register"), *WeaponTag.ToString());
		return;
	}

	CharacterCarriedWeaponMap.Emplace(WeaponTag, SpwanWeapon);

	SpwanWeapon->OnWeaponHitTarget.Unbind();
	SpwanWeapon->OnWeaponPulledFromTarget.Unbind();

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

		WeaponToDestroy->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
		WeaponToDestroy->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnPulledFromTargetActor);

		if (CurrentEquippedWeaponTag == WeaponTag)
		{
			CurrentEquippedWeaponTag = FGameplayTag();
		}

		WeaponToDestroy->Destroy();
	}
}

AWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag WeaponTag) const
{
	if (!WeaponTag.IsValid()) 
	{
		UE_LOG(LogTemp, Display, TEXT("Get WeaponTag is nullptr"));
		return nullptr; 
	}
	if (!CharacterCarriedWeaponMap.Contains(WeaponTag)) 
	{ 
		UE_LOG(LogTemp, Display, TEXT("Get WeaponTag %s Cant' Found"), *WeaponTag.ToString());
		return nullptr; 
	}

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

void UPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType DamageType)
{
	if (DamageType == EToggleDamageType::CurrentEquippedWeapon)
	{
		AWeaponBase* WeaponToToggle = GetCharacterCurrentEquippedWeapon();

		if (!WeaponToToggle) { return; }

		if (bShouldEnable)
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			UE_LOG(LogTemp, Display, TEXT("%s Set Collision Enabled: QueryOnly"), *WeaponToToggle->GetName());
		}
		else
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			UE_LOG(LogTemp, Display, TEXT("%s Set Collision Enabled: NoCollision"), *WeaponToToggle->GetName());
		}
	}
}

void UPawnCombatComponent::OnHitTargetActor(AActor* TargetActor)
{

}

void UPawnCombatComponent::OnPulledFromTargetActor(AActor* TargetActor)
{

}
