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

	// 并不是解引用指针的操作，而是 FString 类型的 operator* 重载，用于获取 FString 对象的内部字符数组（TCHAR*）
	const FString WeaponString = FString::Printf(TEXT("A weapon named %s has been registered using the tag %s"), *InWeaponToRegister->GetName(), *InWeaponTagToRegister.ToString());
	Debug::Print(WeaponString);
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
