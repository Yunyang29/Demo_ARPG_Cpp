#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/CombatComponent_Base.h"
#include "CombatComponent_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UCombatComponent_Enemy : public UCombatComponent_Base
{
	GENERATED_BODY()

public:
	virtual void OnWeaponHitTargetActor(AActor* HitActor) override;
};
