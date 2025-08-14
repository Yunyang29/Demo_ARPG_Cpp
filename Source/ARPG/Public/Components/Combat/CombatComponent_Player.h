#pragma once
#include "CoreMinimal.h"
#include "CombatComponent_Base.h"
#include "CombatComponent_Player.generated.h"

class AWeapon_Player;
/**
 *
 */
UCLASS()
class ARPG_API UCombatComponent_Player : public UCombatComponent_Base
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="A_My|Player|Combat")
	AWeapon_Player* GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	UFUNCTION(BlueprintCallable, Category="A_My|Player|Combat")
	AWeapon_Player* GetPlayerCurEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category="A_My|Player|Combat")
	float GetPlayerCurEquippedWeaponDamageAtLevel(float InLevel) const;

	virtual void OnWeaponHitTargetActor(AActor* HitActor) override;
	virtual void OnWeaponPullFromTargetActor(AActor* InteractedActor) override;
};
