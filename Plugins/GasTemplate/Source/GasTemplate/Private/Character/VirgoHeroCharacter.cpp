// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/VirgoHeroCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"

#include "VirgoGameplayTag.h"
#include "PlayerState/VirgoPlayerState.h"
#include "DataAssets/StartUp/DataAsset_StartUpDataBase.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "DataAssets/StartUp/DataAsset_HeroStartUpData.h"
#include "Components/Input/VirgoInputComponent.h"
#include "AbilitySystem/VirgoAbilitySystemComponent.h"
#include "AbilitySystem/VirgoAttributeSet.h"

AVirgoHeroCharacter::AVirgoHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 90.f);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SocketOffset = FVector(0.f, 0.f, 65.f);
	SpringArm->TargetArmLength = 300.0f;  // 弹簧臂长度
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false;

	// ActorComponents
	GetCharacterMovement()->bUseControllerDesiredRotation = true; // 使用控制器旋转
	GetCharacterMovement()->bOrientRotationToMovement = false;  // 朝向运动方向
    GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->JumpZVelocity = 400.0f;
}

UAbilitySystemComponent* AVirgoHeroCharacter::GetAbilitySystemComponent() const
{
	return GetVirgoAbilitySystemComponent();
}

void AVirgoHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AVirgoPlayerState* VirgoPlayerState = GetPlayerState<AVirgoPlayerState>();

	check(VirgoPlayerState);

	VirgoAbilitySystemComponent = VirgoPlayerState->GetVirgoAbilitySystemComponent();

	VirgoAttributeSet = VirgoPlayerState->GetVirgoAttributeSet();

	VirgoAbilitySystemComponent->InitAbilityActorInfo(VirgoPlayerState, this);

	if (!HeroStartUpConfig.IsNull())
	{
		if (UDataAsset_HeroStartUpData* LoadData = HeroStartUpConfig.LoadSynchronous())
		{
			LoadData->GiveToAbilitySystemComponent(VirgoAbilitySystemComponent);
		}
	}
}

void AVirgoHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(HeroInputConfig);

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	Subsystem->AddMappingContext(HeroInputConfig->DefaultMappingContext, 0);

	UVirgoInputComponent* VirgoInputComponent = CastChecked<UVirgoInputComponent>(PlayerInputComponent);

	VirgoInputComponent->BindNativeInputAction(HeroInputConfig, VirgoGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	VirgoInputComponent->BindNativeInputAction(HeroInputConfig, VirgoGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
	VirgoInputComponent->BindNativeInputAction(HeroInputConfig, VirgoGameplayTags::InputTag_Jump, ETriggerEvent::Started, this, &ThisClass::Input_Jump);

	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AVirgoHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AVirgoHeroCharacter::Input_Move(const FInputActionValue& InputValue)
{
	const FVector2D MovementVector = InputValue.Get<FVector2D>();

	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDir = MovementRotation.RotateVector(FVector::ForwardVector);

		AddMovementInput(ForwardDir, MovementVector.Y);
	}
	if (MovementVector.X != 0.f)
	{
		const FVector RightDir = MovementRotation.RotateVector(FVector::RightVector);

		AddMovementInput(RightDir, MovementVector.X);
	}
}

void AVirgoHeroCharacter::Input_Look(const FInputActionValue& InputValue)
{
	const FVector2D LookVector = InputValue.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(-LookVector.Y);
	}
}

void AVirgoHeroCharacter::Input_Jump(const FInputActionValue& InputValue)
{
	if (GetCharacterMovement()->IsJumpAllowed())
	{
		Jump();
	}
}