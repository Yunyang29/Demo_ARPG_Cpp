#pragma once
#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "StructType_Base.generated.h"

class ULinkedAnimLayer_Player;
class UGameplayAbility_Player;
class UInputMappingContext;

/// @brief 玩家能力
USTRUCT(Blueprintable)
struct FAbilitySet_Player
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag; // 输入绑定tag

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility_Player> AbilityToGrant; // ga

	bool IsValid() const;
};

/// @brief 玩家武器
USTRUCT(BlueprintType)
struct FWeaponData_Player
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ULinkedAnimLayer_Player> WeaponAnimLayerToLink; // 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FAbilitySet_Player> DefaultWeaponAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat WeaponBaseDamage; // 武器基础伤害
};
