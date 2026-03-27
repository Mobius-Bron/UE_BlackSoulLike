// Fill out your copyright notice in the Description page of Project Settings.


#include "VirgoGameplayTag.h"

namespace VirgoGameplayTags
{
	/* Input Tags */
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Equip_Sword, "InputTag.Equip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Unequip_Sword, "InputTag.Unequip.Sword");

	/* Player Tags */
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Sword, "Player.Weapon.Sword");
}
