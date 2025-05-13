#include "Components/Combat/CombatComponent_Player.h"

#include "DebugHelper.h"
#include "Items/Weapons/Weapon_Player.h"

AWeapon_Player* UCombatComponent_Player::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AWeapon_Player>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}
