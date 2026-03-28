// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/VirgoAbilitySystemComponent.h"

UVirgoAbilitySystemComponent::UVirgoAbilitySystemComponent()
{

}

void UVirgoAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) { return; }

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)) { continue; }

		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UVirgoAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) { return; }

}
