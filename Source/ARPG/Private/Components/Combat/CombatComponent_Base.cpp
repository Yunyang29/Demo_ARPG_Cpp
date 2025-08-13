#include "Components/Combat/CombatComponent_Base.h"
#include "Components/BoxComponent.h"
#include "Items/Weapons/Weapon_Base.h"

void UCombatComponent_Base::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWeapon_Base* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!CarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("A named %s has already been added as carried weapon"), *InWeaponTagToRegister.ToString());
	check(InWeaponToRegister);

	CarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);
	InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnWeaponHitTargetActor);
	InWeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnWeaponPullFromTargetActor); // ?
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
	return GetCharacterCarriedWeaponByTag(CurEquippedWeaponTag);
}

void UCombatComponent_Base::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	if(ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
	{
		AWeapon_Base* WeaponToToggle = GetCurEquippedWeapon();
		check(WeaponToToggle);
		if(bShouldEnable)
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
		else
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			OverlappedActors.Empty();
		}
	}
}

void UCombatComponent_Base::OnWeaponHitTargetActor(AActor* HitActor)
{
}

void UCombatComponent_Base::OnWeaponPullFromTargetActor(AActor* InteractedActor)
{
}

//
