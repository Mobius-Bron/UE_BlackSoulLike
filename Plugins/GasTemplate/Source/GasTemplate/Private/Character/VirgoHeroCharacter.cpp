// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/VirgoHeroCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AVirgoHeroCharacter::AVirgoHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 90.f);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SocketOffset = FVector(0.f, 0.f, 65.f);
	SpringArm->TargetArmLength = 300.0f;            // 弹簧臂长度
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	SpringArm->bUsePawnControlRotation = false;

	if (UCharacterMovementComponent* MovementComp = GetCharacterMovement())
	{
		MovementComp->bOrientRotationToMovement = false;  // 朝向运动方向
	}
}