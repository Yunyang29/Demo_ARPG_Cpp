#include "DebugHelper.h"
#include "Components/Combat/CombatComponent_Pawn.h"
#include "Items/Weapons/Weapon_Base.h"

void UCombatComponent_Pawn::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWeapon_Base* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
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


AWeapon_Base* UCombatComponent_Pawn::GetCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if(CarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		// 常量指针，防止通过 Result 修改武器指针本身（如 Result = nullptr 会报错）
		if(AWeapon_Base* const* Result = CarriedWeaponMap.Find(InWeaponTagToGet))
		{
			return *Result;
		}
	}
	return nullptr;
}

AWeapon_Base* UCombatComponent_Pawn::GetCurEquippedWeapon() const
{
	return nullptr;
}
