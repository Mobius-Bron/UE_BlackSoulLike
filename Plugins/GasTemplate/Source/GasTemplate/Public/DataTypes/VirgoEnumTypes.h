// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class EVirgoConfirmType : uint8
{
	YES,
	NO
};

UENUM(BlueprintType)
enum class EVirgoValidType : uint8
{
	Valid,
	Invalid
};

UENUM(BlueprintType)
enum class EVirgoSuccessType : uint8
{
	Successful,
	Failed
};

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand
};