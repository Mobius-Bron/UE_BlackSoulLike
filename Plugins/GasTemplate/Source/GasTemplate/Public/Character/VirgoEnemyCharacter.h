// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/VirgoCharacterBase.h"
#include "AbilitySystemInterface.h"
#include "VirgoEnemyCharacter.generated.h"

class UEnemyCombatComponent;
class UDataAsset_EnemyStartUpData;

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

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Virgo|Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UDataAsset_EnemyStartUpData> EnemyStartUpConfig;

private:
	void InitEnemyStartUpData();

public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};
