// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "VirgoPlayerState.generated.h"

class UVirgoAbilitySystemComponent;
class UVirgoAttributeSet;

/**
 * 
 */
UCLASS()
class GASTEMPLATE_API AVirgoPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AVirgoPlayerState();

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
