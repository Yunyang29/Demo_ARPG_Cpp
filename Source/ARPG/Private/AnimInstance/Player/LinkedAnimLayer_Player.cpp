#include <AnimInstance/Player/LinkedAnimLayer_Player.h>
#include "AnimInstance/Player/AnimInstance_Player.h"

UAnimInstance_Player* ULinkedAnimLayer_Player::GetPlayerAnimInstance() const
{
	return Cast<UAnimInstance_Player>(GetOwningComponent()->GetAnimInstance());
}
