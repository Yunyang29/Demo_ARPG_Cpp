#pragma once

#include "CoreMinimal.h"
#include "AnimInstance/AnimInstance_Base.h"
#include "AnimInstance_Character.generated.h"

class ACharacter_Base;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class ARPG_API UAnimInstance_Character : public UAnimInstance_Base
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	ACharacter_Base* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	bool bHasAcceleration;
};
