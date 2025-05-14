#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUp/DataAsset_StartUp.h"
#include "Types/StructType_Base.h"
#include "DataAsset_StartUp_Player.generated.h"


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
