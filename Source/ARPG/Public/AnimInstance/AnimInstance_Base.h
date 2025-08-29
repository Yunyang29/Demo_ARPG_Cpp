#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AnimInstance_Base.generated.h"

struct FGameplayTag;
/**
 *
 */
UCLASS()
class ARPG_API UAnimInstance_Base : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	bool DoesOwnerHaveTag(FGameplayTag TagToCheck) const;
};
