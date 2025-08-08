#include <AnimInstance/AnimInstance_Character.h>
#include "Characters/Character_Base.h"
#include "GameFramework/CharacterMovementComponent.h"


void UAnimInstance_Character::NativeInitializeAnimation()
{
	OwningCharacter = Cast<ACharacter_Base>(TryGetPawnOwner());
	if(OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UAnimInstance_Character::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if(!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
