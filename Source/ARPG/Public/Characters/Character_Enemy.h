#pragma once

#include "CoreMinimal.h"
#include "Characters/Character_Base.h"
#include "Character_Enemy.generated.h"

class UWidgetComponent;
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
	virtual UUIComponent_Base*     GetUIComponent() const override;
	virtual UUIComponent_Enemy*    GetEnemyUIComponent() const override;

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="A_My|Combat")
	UCombatComponent_Enemy* CombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "A_My|UI")
	UUIComponent_Enemy* UIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "A_My|UI")
	UWidgetComponent* HealthWidgetComponent;

private:
	void InitEnemyStartUpData();

public:
	FORCEINLINE UCombatComponent_Enemy* GetEnemyCombatComp() const { return CombatComponent; }
};
