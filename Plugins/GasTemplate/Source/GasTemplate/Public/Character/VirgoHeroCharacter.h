// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/VirgoCharacterBase.h"
#include "VirgoHeroCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 *
 */
UCLASS()
class GASTEMPLATE_API AVirgoHeroCharacter : public AVirgoCharacterBase
{
	GENERATED_BODY()

public:
	AVirgoHeroCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> Camera;
};