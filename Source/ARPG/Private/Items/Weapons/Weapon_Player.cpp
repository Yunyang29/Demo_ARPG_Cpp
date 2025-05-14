// Fill out your copyright notice in the Description page of Project Settings.


#include <Items/Weapons/Weapon_Player.h>

void AWeapon_Player::AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	GrantedAbilityiesSpecHandles = InSpecHandles;
}

TArray<FGameplayAbilitySpecHandle> AWeapon_Player::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilityiesSpecHandles;
}
