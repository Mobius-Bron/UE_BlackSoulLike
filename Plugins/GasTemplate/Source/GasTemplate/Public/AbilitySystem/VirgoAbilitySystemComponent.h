// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "DataTypes/VirgoStructTypes.h"
#include "VirgoAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class GASTEMPLATE_API UVirgoAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	UVirgoAbilitySystemComponent();

	UFUNCTION(BlueprintCallable, meta = (ApplyLevel = "1"))
	void GrantHeroAbilities(const TArray<FVirgoHeroAbilitySet>& AbilitySet, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandle);

	UFUNCTION(BlueprintCallable, meta = (ApplyLevel = "1"))
	void RemoveHeroAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& AbilitySpecHandlesToRemove);

	void OnAbilityInputPressed(const FGameplayTag& InputTag);
	void OnAbilityInputReleased(const FGameplayTag& InputTag);
};
