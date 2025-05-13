// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatComponent_Base.h"
#include "CombatComponent_Player.generated.h"

class AWeapon_Player;
/**
 * 
 */
UCLASS()
class ARPG_API UCombatComponent_Player : public UCombatComponent_Base
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Player|Combat")
	AWeapon_Player* GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const;
};
