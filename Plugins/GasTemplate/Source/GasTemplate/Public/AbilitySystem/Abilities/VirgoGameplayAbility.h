// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "VirgoGameplayAbility.generated.h"

class UPawnCombatComponent;

UENUM(BlueprintType)
enum class EVirgoAbilityActionPolicy : uint8
{
	OnTriggered,
	OnGiven
};

/**
 * 
 */
UCLASS()
class GASTEMPLATE_API UVirgoGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	/* GameplayAbility */
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	/* GameplayAbility */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VirgoAbility")
	EVirgoAbilityActionPolicy AbilityActionPolicy = EVirgoAbilityActionPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category = "Virgo|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;
};
