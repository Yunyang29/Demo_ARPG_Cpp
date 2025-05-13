// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/Weapon_Base.h"
#include "Types/StructType_Base.h"
#include "Weapon_Player.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API AWeapon_Player : public AWeapon_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WeaponData")
	FWeaponData_Player WeaponData;
};
