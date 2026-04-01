// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS_FunctionLibrary.h"

#include "Components/Combat/PawnCombatComponent.h"
#include "Interfaces/PawnCombatInterface.h"

UPawnCombatComponent* UGAS_FunctionLibrary::NativeGetCombatComponentFromActor(AActor* InActor)
{
    if (!InActor) { return nullptr; }

    if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
    {
        return PawnCombatInterface->GetCombatComponent();
    }

    return nullptr;
}

UPawnCombatComponent* UGAS_FunctionLibrary::BP_GetCombatComponentFromActor(AActor* InActor, EVirgoValidType& ValidType)
{
    UPawnCombatComponent* CombatComponent = NativeGetCombatComponentFromActor(InActor);

    ValidType = CombatComponent ? EVirgoValidType::Valid : EVirgoValidType::Invalid;

    return CombatComponent;
}
