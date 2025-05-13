#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DataAssets/StartUp/DataAsset_StartUp.h"
#include "DataAsset_StartUp_Player.generated.h"

class UGameplayAbility_Player;

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

/**
 * 
 */
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
