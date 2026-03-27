// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/VirgoEnemyGameplayAbility.h"

#include "Character/VirgoEnemyCharacter.h"
#include "Components/Combat/EnemyCombatComponent.h"

AVirgoEnemyCharacter* UVirgoEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedVirgoEnemyCharacter.IsValid())
	{
		CachedVirgoEnemyCharacter = Cast<AVirgoEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedVirgoEnemyCharacter.IsValid() ? CachedVirgoEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UVirgoEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
