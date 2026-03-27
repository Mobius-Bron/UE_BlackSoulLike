// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUp/DataAsset_StartUpDataBase.h"

#include "AbilitySystem/VirgoAbilitySystemComponent.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UVirgoAbilitySystemComponent* InVASCToGive, int32 ApplyLevel)
{
	check(InVASCToGive);

	GrantAbilities(ActivateOnGiveAbilities, InVASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InVASCToGive, ApplyLevel);
}

void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UVirgoGameplayAbility>>& AbilitiesToGive, UVirgoAbilitySystemComponent* InVASCToGive, int32 ApplyLevel)
{
	if (AbilitiesToGive.IsEmpty()) { return; }

	for (const TSubclassOf<UVirgoGameplayAbility>& Ability : AbilitiesToGive)
	{
		if (!Ability) { continue; }

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InVASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InVASCToGive->GiveAbility(AbilitySpec);
	}
}
