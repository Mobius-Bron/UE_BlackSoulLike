// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUp/DataAsset_EnemyStartUpData.h"

void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UVirgoAbilitySystemComponent* InVASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InVASCToGive, ApplyLevel);

	for (const TSubclassOf<UVirgoEnemyGameplayAbility>& EnemyAbilitySet : EnemyStartUpAbilitySets)
	{
		if (EnemyAbilitySet == nullptr) { continue; }

		FGameplayAbilitySpec AbilitySpec(EnemyAbilitySet);
		AbilitySpec.SourceObject = InVASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InVASCToGive->GiveAbility(AbilitySpec);
	}
}
