// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS_FunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "Components/Combat/PawnCombatComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "AbilitySystem/VirgoAbilitySystemComponent.h"

UPawnCombatComponent* UGAS_FunctionLibrary::NativeGetCombatComponentFromActor(AActor* InActor)
{
    if (!InActor) { return nullptr; }

    if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
    {
        return PawnCombatInterface->GetCombatComponent();
    }

    return nullptr;
}

UVirgoAbilitySystemComponent* UGAS_FunctionLibrary::NativeGetVirgoASCFromActor(AActor* InActor)
{
    check(InActor);

    return CastChecked<UVirgoAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UGAS_FunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
    UVirgoAbilitySystemComponent* VirgoASC = NativeGetVirgoASCFromActor(InActor);

    if (!VirgoASC->HasMatchingGameplayTag(TagToAdd))
    {
        VirgoASC->AddLooseGameplayTag(TagToAdd);
    }
}

UPawnCombatComponent* UGAS_FunctionLibrary::BP_GetCombatComponentFromActor(AActor* InActor, EVirgoValidType& ValidType)
{
    UPawnCombatComponent* CombatComponent = NativeGetCombatComponentFromActor(InActor);

    ValidType = CombatComponent ? EVirgoValidType::Valid : EVirgoValidType::Invalid;

    return CombatComponent;
}
