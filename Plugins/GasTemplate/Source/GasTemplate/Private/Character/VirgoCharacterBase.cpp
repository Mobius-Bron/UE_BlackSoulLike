// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/VirgoCharacterBase.h"

#include "AbilitySystem/VirgoAbilitySystemComponent.h"
#include "AbilitySystem/VirgoAttributeSet.h"

AVirgoCharacterBase::AVirgoCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	// 默认不接收和显示贴花
	GetMesh()->bReceivesDecals = false;
}
