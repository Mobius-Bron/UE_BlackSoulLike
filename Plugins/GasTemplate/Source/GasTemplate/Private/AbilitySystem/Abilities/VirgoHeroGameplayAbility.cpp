// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/VirgoHeroGameplayAbility.h"

#include "VirgoGameplayTag.h"
#include "Character/VirgoHeroCharacter.h"
#include "Controller/VirgoController.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "AbilitySystem/VirgoAbilitySystemComponent.h"

AVirgoHeroCharacter* UVirgoHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	if (!CachedVirgoHeroCharacter.IsValid())
	{
		CachedVirgoHeroCharacter = Cast<AVirgoHeroCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedVirgoHeroCharacter.IsValid() ? CachedVirgoHeroCharacter.Get() : nullptr;
}

AVirgoController* UVirgoHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	if (!CachedVirgoController.IsValid())
	{
		CachedVirgoController = Cast<AVirgoController>(CurrentActorInfo->PlayerController);
	}

	return CachedVirgoController.IsValid() ? CachedVirgoController.Get() : nullptr;
}

UHeroCombatComponent* UVirgoHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}

FGameplayEffectSpecHandle UVirgoHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage)
{
	check(EffectClass);
	FGameplayEffectContextHandle ContextHandle = GetVirgoAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = GetVirgoAbilitySystemComponent()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		VirgoGameplayTags::Shared_SetByCaller_BaseDamage,
		InWeaponBaseDamage
	);

	return EffectSpecHandle;
}
