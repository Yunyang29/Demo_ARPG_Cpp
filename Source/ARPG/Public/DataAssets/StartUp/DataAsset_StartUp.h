
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUp.generated.h"

class UMainGameplayAbility;
class UMainAbilitySystemComponent;
/**
 *
 */
UCLASS()
class ARPG_API UDataAsset_StartUp : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UMainAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UMainGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UMainGameplayAbility>> ReactiveAbilities;

	void GrantAbilities(const TArray<TSubclassOf<UMainGameplayAbility>>& InAbilitiesToGive, UMainAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
};
