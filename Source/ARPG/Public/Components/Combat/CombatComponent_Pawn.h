#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponent_Base.h"
#include "GameplayTagContainer.h"
#include "CombatComponent_Pawn.generated.h"

class AWeapon_Base;
/**
 * 
 */
UCLASS()
class ARPG_API UCombatComponent_Pawn : public UPawnExtensionComponent_Base
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category ="Warrior|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWeapon_Base* InWeaponToRegister, bool bRegisterAsEquippedWeapon);

	UFUNCTION(BlueprintCallable, Category ="Warrior|Combat")
	AWeapon_Base* GetCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;	//此函数是常量成员函数，承诺不会修改类的成员变量（即 UCombatComponent_Pawn 的状态）。

	UPROPERTY(BlueprintReadWrite, Category="Warrior|Combat")
	FGameplayTag CurEquippedWeaponTag;

	UFUNCTION(BlueprintCallable, Category="Warrior|Combat")
	AWeapon_Base* GetCurEquippedWeapon() const;

private:
	TMap<FGameplayTag, AWeapon_Base*> CarriedWeaponMap;
};
