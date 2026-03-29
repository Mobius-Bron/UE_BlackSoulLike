// Fill out your copyright notice in the Description page of Project Settings.


#include "VirgoGameplayTag.h"

namespace VirgoGameplayTags
{
	/* Input Tags */
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Equip, "InputTag.Equip");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Unequip, "InputTag.Unequip");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack, "InputTag.Attack");

	/* Player Tags */
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip, "Player.Ability.Equip");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip, "Player.Ability.Unequip");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Sword, "Player.Ability.Attack.Sword");

	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Sword, "Player.Weapon.Sword");

	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip, "Player.Event.Equip");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Unequip, "Player.Event.Unequip");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Attack_Sword, "Player.Event.Attack.Sword");
}
