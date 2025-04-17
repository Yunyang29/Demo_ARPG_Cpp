#include "AbilitySystem/Abilities/GameplayAbility_Player.h"
#include "Characters/Character_Player.h"
#include "Controllers/PlayerController_Base.h"

ACharacter_Player* UGameplayAbility_Player::GetPlayerFromActorInfo()
{
	if(!CachedPlayer.IsValid())
	{
		CachedPlayer = Cast<ACharacter_Player>(CurrentActorInfo->AvatarActor);
	}
	return CachedPlayer.IsValid() ? CachedPlayer.Get() : nullptr;
}

APlayerController_Base* UGameplayAbility_Player::GetPlayerControllerFromActorInfo()
{
	if(!CachedPlayerController.IsValid())
	{
		CachedPlayerController = Cast<APlayerController_Base>(CurrentActorInfo->PlayerController);
	}
	return CachedPlayerController.IsValid() ? CachedPlayerController.Get() : nullptr;
}

UCombatComponent_Player* UGameplayAbility_Player::GetCombatComponentFromActorInfo()
{
	return GetPlayerFromActorInfo()->GetCombatComponent();
}
