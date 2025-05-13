#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponent_Base.h"
#include "GameplayTagContainer.h"
#include "CombatComponent_Base.generated.h"

class AWeapon_Base;
/**
 * 
 */
UCLASS()
class ARPG_API UCombatComponent_Base : public UPawnExtensionComponent_Base
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category ="Character|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWeapon_Base* InWeaponToRegister, bool bRegisterAsEquippedWeapon);

	UFUNCTION(BlueprintCallable, Category ="Character|Combat")
	AWeapon_Base* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;	//此函数是常量成员函数，承诺不会修改类的成员变量（即 UCombatComponent_Base 的状态）。

	UPROPERTY(BlueprintReadWrite, Category="Character|Combat")
	FGameplayTag CurEquippedWeaponTag;

	UFUNCTION(BlueprintCallable, Category="Character|Combat")
	AWeapon_Base* GetCurEquippedWeapon() const;

private:
	TMap<FGameplayTag, AWeapon_Base*> CarriedWeaponMap;
};
