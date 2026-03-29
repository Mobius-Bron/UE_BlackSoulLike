// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUp/DataAsset_StartUpDataBase.h"

#include "DataTypes/VirgoStructTypes.h"
#include "DataAsset_HeroStartUpData.generated.h"


/**
 * 
 */
UCLASS()
class GASTEMPLATE_API UDataAsset_HeroStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UVirgoAbilitySystemComponent* InVASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditAnywhere, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FVirgoHeroAbilitySet> HeroStartUpAbilitySets;
};
