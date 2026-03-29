// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/VirgoAbilitySystemComponent.h"

UVirgoAbilitySystemComponent::UVirgoAbilitySystemComponent()
{

}

void UVirgoAbilitySystemComponent::GrantHeroAbilities(const TArray<FVirgoHeroAbilitySet>& AbilitySet, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandle)
{
	if (AbilitySet.IsEmpty()) { return; }

	for (const FVirgoHeroAbilitySet& HeroAbilitySet : AbilitySet)
	{
		if (!HeroAbilitySet.IsValid()) { continue; }

		FGameplayAbilitySpec AbilitySpec(HeroAbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = this->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(HeroAbilitySet.InputTag);

		this->GiveAbility(AbilitySpec);

		OutGrantedAbilitySpecHandle.AddUnique(GiveAbility(AbilitySpec));
	}
}

void UVirgoAbilitySystemComponent::RemoveHeroAbilities(UPARAM(ref)TArray<FGameplayAbilitySpecHandle>& AbilitySpecHandlesToRemove)
{
	if (AbilitySpecHandlesToRemove.IsEmpty()) { return; }

	for (const FGameplayAbilitySpecHandle& SpecHandle : AbilitySpecHandlesToRemove)
	{
		if (!SpecHandle.IsValid()) { continue; }

		ClearAbility(SpecHandle);
	}

	AbilitySpecHandlesToRemove.Empty();
}

void UVirgoAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) { return; }

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag)) { continue; }

		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UVirgoAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) { return; }

}
