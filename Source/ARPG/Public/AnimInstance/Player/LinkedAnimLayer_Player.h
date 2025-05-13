#pragma once

#include "CoreMinimal.h"
#include "AnimInstance/AnimInstance_Base.h"
#include "LinkedAnimLayer_Player.generated.h"

class UAnimInstance_Player;
/**
 * 
 */
UCLASS()
class ARPG_API ULinkedAnimLayer_Player : public UAnimInstance_Base
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	UAnimInstance_Player* GetPlayerAnimInstance() const;
};
