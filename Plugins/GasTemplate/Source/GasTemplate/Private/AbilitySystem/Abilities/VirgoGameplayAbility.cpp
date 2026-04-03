// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/VirgoGameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "AbilitySystem/VirgoAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"

void UVirgoGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActionPolicy == EVirgoAbilityActionPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UVirgoGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActionPolicy == EVirgoAbilityActionPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UPawnCombatComponent* UVirgoGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->GetComponentByClass<UPawnCombatComponent>();
}

UVirgoAbilitySystemComponent* UVirgoGameplayAbility::GetVirgoAbilitySystemComponent() const
{
	return Cast<UVirgoAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle UVirgoGameplayAbility::NativeApplyEffectHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	if (!TargetASC || !InSpecHandle.IsValid()) { return FActiveGameplayEffectHandle(); }

	return GetVirgoAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(
		*InSpecHandle.Data,
		TargetASC
	);
}

FActiveGameplayEffectHandle UVirgoGameplayAbility::BP_ApplyEffectHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EVirgoSuccessType& SuccessType)
{
	FActiveGameplayEffectHandle EffectHandle = NativeApplyEffectHandleToTarget(TargetActor, InSpecHandle);

	SuccessType = EffectHandle.WasSuccessfullyApplied() ? EVirgoSuccessType::Successful : EVirgoSuccessType::Failed;

	return EffectHandle;
}
