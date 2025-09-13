#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Interfaces/PawnUIInterface.h"
#include "Character_Base.generated.h"

class UAbilitySystemComponent_Base;
class UAttributeSet_Base;
class UDataAsset_StartUp;
class UMotionWarpingComponent;

UCLASS()
class ARPG_API ACharacter_Base : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface, public IPawnUIInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacter_Base();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual UCombatComponent_Base* GetCombatComponent() const override;

	virtual UUIComponent_Base* GetUIComponent() const override;

protected:
	//~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "A_My|AbilitySystem")
	UAbilitySystemComponent_Base* ASC; /// Character's Ability System Component

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "A_My|AbilitySystem")
	UAttributeSet_Base* AS; /// Character's Attribute Set

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "A_My|MotionWarping")
	UMotionWarpingComponent* MWC;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "A_My|CharacterData")
	TSoftObjectPtr<UDataAsset_StartUp> StartUpData; /// Character's Start Up Data

public:
	FORCEINLINE UAbilitySystemComponent_Base* GetCharacterAbilitySystemComponent() const { return ASC; } /// 获取角色的能力系统组件
	FORCEINLINE UAttributeSet_Base* GetCharacterAttributeSet() const { return AS; } /// 获取角色的属性集
};
