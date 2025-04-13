#pragma once

#include "CoreMinimal.h"
#include "AnimInstance/CharacterAnimInstance.h"
#include "Characters/PlayerCharacter.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UPlayerAnimInstance : public UCharacterAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|References")
	APlayerCharacter* OwningPlayerCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	bool bShouldEnterRelaxState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	float EnterRelaxStateThreshold = 5.f;
	
	float IdleElapsedTime;
};
