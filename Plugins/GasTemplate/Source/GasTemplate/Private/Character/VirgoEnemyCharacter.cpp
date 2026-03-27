// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/VirgoEnemyCharacter.h"

#include "AbilitySystem/VirgoAbilitySystemComponent.h"
#include "AbilitySystem/VirgoAttributeSet.h"
#include "Components/Combat/EnemyCombatComponent.h"

AVirgoEnemyCharacter::AVirgoEnemyCharacter()
{
	VirgoAbilitySystemComponent = CreateDefaultSubobject<UVirgoAbilitySystemComponent>(TEXT("VirgoAbilitySystemComponent"));

	VirgoAttributeSet = CreateDefaultSubobject<UVirgoAttributeSet>(TEXT("VirgoAttributeSet"));

	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));
}

UAbilitySystemComponent* AVirgoEnemyCharacter::GetAbilitySystemComponent() const
{
	return GetVirgoAbilitySystemComponent();
}

void AVirgoEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	VirgoAbilitySystemComponent->InitAbilityActorInfo(this, this);
}
