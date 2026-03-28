// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUp/DataAsset_HeroStartUpData.h"

#include "AbilitySystem/VirgoAbilitySystemComponent.h"

void UDataAsset_HeroStartUpData::GiveToAbilitySystemComponent(UVirgoAbilitySystemComponent* InVASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InVASCToGive, ApplyLevel);

	for (const FVirgoHeroAbilitySet& HeroAbilitySet : HeroStartUpAbilitySets)
	{
		if (!HeroAbilitySet.IsValid()) { continue; }

		FGameplayAbilitySpec AbilitySpec(HeroAbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InVASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(HeroAbilitySet.InputTag);

		InVASCToGive->GiveAbility(AbilitySpec);
	}
}
