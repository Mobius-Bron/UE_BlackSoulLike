// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/VirgoCharacterBase.h"
#include "AbilitySystemInterface.h"
#include "VirgoEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GASTEMPLATE_API AVirgoEnemyCharacter : 
	public AVirgoCharacterBase,
	public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AVirgoEnemyCharacter();

	/* IAbilitySystemInterface */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	/* IAbilitySystemInterface */

	void BeginPlay() override;
};
