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

USTRUCT(Blueprintable)
struct FSpecialAbilitySet_Player : public FAbilitySet_Player
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UMaterialInterface> SoftIconMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Player.Cooldown"))
	FGameplayTag CooldownTag;
};

/// @brief 玩家武器
USTRUCT(BlueprintType)
struct FWeaponData_Player
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ULinkedAnimLayer_Player> AnimLayerToLink; // 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FAbilitySet_Player> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FSpecialAbilitySet_Player> SpecialAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat BaseDamage; // 武器基础伤害

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> SoftIconTexture;
};
