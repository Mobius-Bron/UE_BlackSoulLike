// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/EquipItemBase.h"
#include "WeaponBase.generated.h"

class USkeletalMeshComponent;
class UBoxComponent;

/**
 * 
 */
UCLASS()
class GASTEMPLATE_API AWeaponBase : public AEquipItemBase
{
	GENERATED_BODY()

public:
	AWeaponBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Waepon")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Waepon")
	TObjectPtr<UBoxComponent> WeaponCollisionBox;

public:
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const
	{
		return WeaponCollisionBox;
	}
};
