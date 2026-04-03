// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Calculation/GEEC_DamageTake.h"
#include "AbilitySystem/VirgoAttributeSet.h"


struct FVirgoCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken);

	FVirgoCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UVirgoAttributeSet, AttackPower, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UVirgoAttributeSet, DefensePower, Target, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UVirgoAttributeSet, DamageTaken, Target, false);
	}
};

static const FVirgoCapture& GetVirgoCapture()
{
	static FVirgoCapture VirgoCapture;
	return VirgoCapture;
}

UGEEC_DamageTake::UGEEC_DamageTake()
{
	RelevantAttributesToCapture.Add(GetVirgoCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetVirgoCapture().DefensePowerDef);

	RelevantAttributesToCapture.Add(GetVirgoCapture().DamageTakenDef);
}

void UGEEC_DamageTake::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams, 
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput
) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	//EffectSpec.GetContext().GetSourceObject();
	//EffectSpec.GetContext().GetAbility();
	//EffectSpec.GetContext().GetInstigator();
	//EffectSpec.GetContext().GetEffectCauser();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.0f;
	float TargetDefensePower = 0.0f;

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		GetVirgoCapture().AttackPowerDef, 
		EvaluateParameters, 
		SourceAttackPower
	);

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		GetVirgoCapture().DefensePowerDef,
		EvaluateParameters,
		TargetDefensePower
	);

	const float FinalDamageDone = FMath::Max(0.0f, SourceAttackPower - TargetDefensePower);

	OutExecutionOutput.AddOutputModifier(
		FGameplayModifierEvaluatedData(
			GetVirgoCapture().DamageTakenProperty,
			EGameplayModOp::Override,
			FinalDamageDone
		)
	);
}
