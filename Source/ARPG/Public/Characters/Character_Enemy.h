#pragma once

#include "CoreMinimal.h"
#include "Characters/Character_Base.h"
#include "Character_Enemy.generated.h"

class UUIComponent_Enemy;
class UCombatComponent_Enemy;
/**
 * 
 */
UCLASS()
class ARPG_API ACharacter_Enemy : public ACharacter_Base
{
	GENERATED_BODY()

public:
	ACharacter_Enemy();
	virtual UCombatComponent_Base* GetCombatComponent() const override;
	virtual UUIComponent_Base* GetUIComponent() const override;

protected:
	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	UCombatComponent_Enemy* CombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "UI", meta = (ALLowPrivateAccess = "true"))
	UUIComponent_Enemy* UIComponent;

private:
	void InitEnemyStartUpData();

public:
	FORCEINLINE UCombatComponent_Enemy* GetEnemyCombatComp() const { return CombatComponent; }
};
