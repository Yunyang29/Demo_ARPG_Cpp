
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUp.generated.h"

class UGameplayAbility_Base;
class UAbilitySystemComponent_Base;
/**
 *
 */
UCLASS()
class ARPG_API UDataAsset_StartUp : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UAbilitySystemComponent_Base* InASCToGive, int32 ApplyLevel = 1);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UGameplayAbility_Base>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UGameplayAbility_Base>> ReactiveAbilities;

	void GrantAbilities(const TArray<TSubclassOf<UGameplayAbility_Base>>& InAbilitiesToGive, UAbilitySystemComponent_Base* InASCToGive, int32 ApplyLevel = 1);
};
