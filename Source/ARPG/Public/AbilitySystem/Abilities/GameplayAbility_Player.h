#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GameplayAbility_Base.h"
#include "GameplayAbility_Player.generated.h"

class ACharacter_Player;
class APlayerController_Base;
class UCombatComponent_Player;


/**
 *
 */
UCLASS()
class ARPG_API UGameplayAbility_Player : public UGameplayAbility_Base
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "A_My|Player|Ability")
	ACharacter_Player* GetPlayerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "A_My|Player|Ability")
	APlayerController_Base* GetPlayerControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "A_My|Player|Ability")
	UCombatComponent_Player* GetPlayerCombatCompFromActorInfo();

private:
	// smart pointer holds reference
	TWeakObjectPtr<ACharacter_Player> CachedPlayer;
	TWeakObjectPtr<APlayerController_Base> CachedPlayerController;
};
