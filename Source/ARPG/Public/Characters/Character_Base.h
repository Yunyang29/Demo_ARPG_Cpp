#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Character_Base.generated.h"

class UAbilitySystemComponent_Base;
class UAttributeSet_Base;
class UDataAsset_StartUp;

UCLASS()
class ARPG_API ACharacter_Base : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacter_Base();

	//~ Begin IAbilitySystemInterface Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface Interface

protected:
	//~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "AbilitySystem")
	UAbilitySystemComponent_Base* ASC; /// Character's Ability System Component

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "AbilitySystem")
	UAttributeSet_Base* AS; /// Character's Attribute Set

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUp> StartUpData; /// Character's Start Up Data

public:
	FORCEINLINE UAbilitySystemComponent_Base* GetCharacterAbilitySystemComponent() const { return ASC; } /// 获取角色的能力系统组件
	FORCEINLINE UAttributeSet_Base* GetCharacterAttributeSet() const { return AS; } /// 获取角色的属性集
};
