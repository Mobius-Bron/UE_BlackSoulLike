// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "GameplayTagContainer.h"

#include "DataTypes/VirgoEnumTypes.h"
#include "Items/Weapons/VirgoHeroWeapon.h"
#include "PawnCombatComponent.generated.h"

/**
 * 
 */
UCLASS()
class GASTEMPLATE_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Virgo|Combat")
	void RegisterSpawnedWeapon(FGameplayTag WeaponTag, AWeaponBase* SpwanWeapon, bool RegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category = "Virgo|Combat")
	void UnregisterAndDestoryWeapon(FGameplayTag WeaponTag);

	UFUNCTION(BlueprintCallable, Category = "Virgo|Combat")
	AWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag WeaponTag) const;

	UFUNCTION(BlueprintCallable, Category = "Virgo|Combat")
	AWeaponBase* GetCharacterCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Virgo|Combat")
	void ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType DamageType = EToggleDamageType::CurrentEquippedWeapon);

	virtual void OnHitTargetActor(AActor* TargetActor);
	virtual void OnPulledFromTargetActor(AActor* TargetActor);

	UPROPERTY(BlueprintReadWrite, Category = "Virgo|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

protected:
	TArray<AActor*> OverlappedActors;

	TMap<FGameplayTag, AWeaponBase*> CharacterCarriedWeaponMap;
};
