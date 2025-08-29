#include "AnimInstance/AnimInstance_Base.h"

#include "FunctionLibrary_Base.h"

bool UAnimInstance_Base::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if(APawn* OwningPawn = TryGetPawnOwner())
	{
		return UFunctionLibrary_Base::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}
	return false;
}
