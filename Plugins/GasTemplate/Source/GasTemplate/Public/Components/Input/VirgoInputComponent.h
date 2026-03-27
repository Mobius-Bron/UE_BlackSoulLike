// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"

#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "VirgoInputComponent.generated.h"

class UInputAction;

/**
 * 
 */
UCLASS()
class GASTEMPLATE_API UVirgoInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);

	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc PressedFunc, CallbackFunc RelasedFunc);
};

template<class UserObject, typename CallbackFunc>
inline void UVirgoInputComponent::BindNativeInputAction(UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	check(InInputConfig);

	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(
			FoundAction, 
			TriggerEvent, 
			ContextObject, 
			Func
		);
	}
}

template<class UserObject, typename CallbackFunc>
inline void UVirgoInputComponent::BindAbilityInputAction(UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc PressedFunc, CallbackFunc RelasedFunc)
{
	check(InInputConfig);

	for (const FVirgoInputActionConfig AbilityInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if (!AbilityInputActionConfig.IsValid()) { continue; }

		BindAction(
			AbilityInputActionConfig.InputAction, 
			ETriggerEvent::Started, 
			ContextObject,
			PressedFunc,
			AbilityInputActionConfig.InputTag
		);
		BindAction(
			AbilityInputActionConfig.InputAction,
			ETriggerEvent::Completed,
			ContextObject,
			RelasedFunc,
			AbilityInputActionConfig.InputTag
		);
	}
}
