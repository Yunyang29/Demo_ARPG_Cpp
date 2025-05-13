#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DataAssets/StartUp/DataAsset_StartUp.h"
#include "DataAsset_StartUp_Player.generated.h"

class UGameplayAbility_Player;

/// @brief 玩家能力的预设数据结构
USTRUCT(Blueprintable)
struct FAbilitySet_Player
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility_Player> AbilityToGrant;

	bool IsValid() const;
};


/// @brief 玩家角色的启动数据资产类
UCLASS()
class ARPG_API UDataAsset_StartUp_Player : public UDataAsset_StartUp
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UAbilitySystemComponent_Base* InASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FAbilitySet_Player> StartUpAbilitySets;
};
