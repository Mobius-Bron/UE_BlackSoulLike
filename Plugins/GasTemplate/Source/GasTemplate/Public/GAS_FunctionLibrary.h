// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataTypes/VirgoEnumTypes.h"
#include "GAS_FunctionLibrary.generated.h"

class UPawnCombatComponent;

/**
 * 
 */
UCLASS()
class GASTEMPLATE_API UGAS_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static UPawnCombatComponent* NativeGetCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Virgo|BlueprintFunctionLibrary", meta = (DisplayName = "Get pawn combat component", ExpandEnumAsExecs = "ValidType"))
	static UPawnCombatComponent* BP_GetCombatComponentFromActor(AActor* InActor, EVirgoValidType& ValidType);
};
