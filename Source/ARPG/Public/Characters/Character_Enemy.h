#pragma once

#include "CoreMinimal.h"
#include "Characters/Character_Base.h"
#include "Components/Combat/CombatComponent_Enemy.h"
#include "Character_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API ACharacter_Enemy : public ACharacter_Base
{
	GENERATED_BODY()

public:
	ACharacter_Enemy();

protected:
	virtual void PossessedBy(AController* NewController) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	UCombatComponent_Enemy* CombatComponent;

private:
	void InitEnemyStartUpData();

public:
	FORCEINLINE UCombatComponent_Enemy* GetEnemyCombatComp() const { return CombatComponent; }
};
