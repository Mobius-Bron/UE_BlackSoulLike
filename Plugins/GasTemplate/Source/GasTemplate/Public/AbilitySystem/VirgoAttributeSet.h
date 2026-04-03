// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/VirgoAbilitySystemComponent.h"
#include "VirgoAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class GASTEMPLATE_API UVirgoAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UVirgoAttributeSet();

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = "Attribute|Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UVirgoAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Attribute|Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UVirgoAttributeSet, CurrentHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Attribute|Attack")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UVirgoAttributeSet, AttackPower);

	UPROPERTY(BlueprintReadOnly, Category = "Attribute|Defense")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UVirgoAttributeSet, DefensePower);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attribute|Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UVirgoAttributeSet, DamageTaken);
};
