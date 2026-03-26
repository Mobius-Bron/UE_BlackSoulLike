// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "InputAction.h"
#include "InputMappingContext.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag)
{
	for (FVirgoInputActionConfig& InputActionConfig : NativeInputAction)
	{
		if (InputActionConfig.InputTag == InInputTag)
		{
			return InputActionConfig.InputAction;
		}
	}

	return nullptr;
}
