#include "DebugHelper.h"
#include "Components/Combat/CombatComponent_Base.h"
#include "Items/Weapons/Weapon_Base.h"

void UCombatComponent_Base::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWeapon_Base* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!CarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("A named %s has already been added as carried weapon"), *InWeaponTagToRegister.ToString());
	check(InWeaponToRegister);

	CarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);
	if(bRegisterAsEquippedWeapon)
	{
		CurEquippedWeaponTag = InWeaponTagToRegister;
	}
}


AWeapon_Base* UCombatComponent_Base::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if(CarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		if(AWeapon_Base* const* Result = CarriedWeaponMap.Find(InWeaponTagToGet))
		{
			return *Result;
		}
	}
	return nullptr;
}

AWeapon_Base* UCombatComponent_Base::GetCurEquippedWeapon() const
{
	return nullptr;
}
