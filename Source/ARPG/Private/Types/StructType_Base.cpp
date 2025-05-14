#include "Types/StructType_Base.h"
#include "AbilitySystem/Abilities/GameplayAbility_Player.h"

bool FAbilitySet_Player::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
