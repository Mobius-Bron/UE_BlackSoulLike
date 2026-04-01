// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnCombatInterface.h"
#include "VirgoCharacterBase.generated.h"

class UVirgoAbilitySystemComponent;
class UVirgoAttributeSet;

UCLASS()
class GASTEMPLATE_API AVirgoCharacterBase : 
	public ACharacter,
	public IAbilitySystemInterface,
	public IPawnCombatInterface
{
	GENERATED_BODY()

public:
	AVirgoCharacterBase();

	/* IAbilitySystemInterface */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	/* IAbilitySystemInterface */

	/* IPawnCombatInterface */
	virtual UPawnCombatComponent* GetCombatComponent() const override;
	/* IPawnCombatInterface */

protected:
#pragma endregion AbilitySystem
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UVirgoAbilitySystemComponent> VirgoAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UVirgoAttributeSet> VirgoAttributeSet;
#pragma endregion

public:
	FORCEINLINE UVirgoAbilitySystemComponent* GetVirgoAbilitySystemComponent() const
	{
		return VirgoAbilitySystemComponent;
	}

	FORCEINLINE UVirgoAttributeSet* GetVirgoAttributeSet() const
	{
		return VirgoAttributeSet;
	}
};
