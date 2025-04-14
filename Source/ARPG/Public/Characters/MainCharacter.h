#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "MainCharacter.generated.h"

class UMainAbilitySystemComponent;
class UMainAttributeSet;
class UDataAsset_StartUp;

UCLASS()
class ARPG_API AMainCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	//~ Begin IAbilitySystemInterface Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface Interface

protected:
	//~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "AbilitySystem")
	UMainAbilitySystemComponent* CharacterAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "AbilitySystem")
	UMainAttributeSet* CharacterAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUp> CharacterStartUpData;

public:
	FORCEINLINE UMainAbilitySystemComponent* GetCharacterAbilitySystemComponent() const { return CharacterAbilitySystemComponent; }
	FORCEINLINE UMainAttributeSet* GetCharacterAttributeSet() const { return CharacterAttributeSet; }
};
