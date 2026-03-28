// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace VirgoGameplayTags
{
	/* Input Tags */
	GASTEMPLATE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	GASTEMPLATE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	GASTEMPLATE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Jump);
	GASTEMPLATE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Equip_Sword);
	GASTEMPLATE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Unequip_Sword);

	/* Player Tags */
	GASTEMPLATE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Sword);

	GASTEMPLATE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Sword);
	GASTEMPLATE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Sword);
	GASTEMPLATE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Attack_Sword);
}