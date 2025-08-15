#include "AbilitySystem/AttributeSet_Base.h"

#include "DebugHelper.h"
#include "FunctionLibrary_Base.h"
#include "GameplayEffectExtension.h"
#include "GameplayTags_Base.h"

UAttributeSet_Base::UAttributeSet_Base()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}

void UAttributeSet_Base::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if(Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 1.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);
	}

	if(Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 1.f, GetMaxRage());
		SetCurrentRage(NewCurrentRage);
	}

	if(Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();
		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);

		Debug::Print(TEXT("NewCurrentHealth %s"), NewCurrentHealth);

		// TODO Notify the UI
		if(NewCurrentHealth == 0.f)
		{
			UFunctionLibrary_Base::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), GameplayTags_Base::Shared_Status_Death);
		}
	}
}
