// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilitySystem/VirgoAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/VirgoGameplayAbility.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UVirgoAbilitySystemComponent;
class UVirgoGameplayAbility;

/**
 * 
 */
UCLASS()
class GASTEMPLATE_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()
	
public:
	virtual void GiveToAbilitySystemComponent(UVirgoAbilitySystemComponent* InVASCToGive, int32 ApplyLevel = 1);

protected:
	UPROPERTY(EditAnywhere, Category = "StartUpData")
	TArray<TSubclassOf<UVirgoGameplayAbility>> ActivateOnGiveAbilities;

	UPROPERTY(EditAnywhere, Category = "StartUpData")
	TArray<TSubclassOf<UVirgoGameplayAbility>> ReactiveAbilities;

	void GrantAbilities(const TArray<TSubclassOf<UVirgoGameplayAbility>>& AbilitiesToGive, UVirgoAbilitySystemComponent* InVASCToGive, int32 ApplyLevel = 1);
};
