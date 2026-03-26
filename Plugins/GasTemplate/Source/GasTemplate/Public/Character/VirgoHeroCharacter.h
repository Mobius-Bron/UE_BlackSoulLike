// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/VirgoCharacterBase.h"
#include "InputActionValue.h"
#include "VirgoHeroCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

class UDataAsset_InputConfig;

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
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

#pragma endregion Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;
#pragma endregion

#pragma endregion Inputs
	void Input_Move(const FInputActionValue& InputValue);
	void Input_Look(const FInputActionValue& InputValue);
	void Input_Jump(const FInputActionValue& InputValue);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDataAsset_InputConfig> HeroInputConfig;
#pragma endregion
};