#include "Components/Combat/CombatComponent_Player.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Items/Weapons/Weapon_Player.h"
#include "GameplayTags_Base.h"

AWeapon_Player* UCombatComponent_Player::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AWeapon_Player>(GetCarriedWeaponByTag(InWeaponTag));
}

AWeapon_Player* UCombatComponent_Player::GetPlayerCurEquippedWeapon() const
{
	return Cast<AWeapon_Player>(GetCurEquippedWeapon());
}

float UCombatComponent_Player::GetPlayerCurEquippedWeaponDamageAtLevel(float InLevel) const
{
	return GetPlayerCurEquippedWeapon()->WeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UCombatComponent_Player::OnWeaponHitTargetActor(AActor* HitActor)
{
	if(OverlappedActors.Contains(HitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(HitActor);

	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), GameplayTags_Base::Shared_Event_MeleeHit, Data); // ?
}

void UCombatComponent_Player::OnWeaponPullFromTargetActor(AActor* InteractedActor)
{
	// Debug::Print(InteractedActor->GetActorNameOrLabel());
}
