#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AttributeSet_Base.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

class IPawnUIInterface;
/**
 * 
 */
UCLASS()
class ARPG_API UAttributeSet_Base : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAttributeSet_Base();

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// ? 会自动生成？
	UPROPERTY(BlueprintReadOnly, Category="Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Base, CurrentHealth);

	UPROPERTY(BlueprintReadOnly, Category="Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Base, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category="Rage")
	FGameplayAttributeData CurrentRage;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Base, CurrentRage);

	UPROPERTY(BlueprintReadOnly, Category="Rage")
	FGameplayAttributeData MaxRage;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Base, MaxRage);

	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Base, AttackPower);

	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Base, DefensePower);

	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UAttributeSet_Base, DamageTaken);

private:
	TWeakInterfacePtr<IPawnUIInterface> CachedPawnUIInterface;
};
