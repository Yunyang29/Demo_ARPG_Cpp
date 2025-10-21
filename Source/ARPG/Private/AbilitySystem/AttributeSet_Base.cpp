#include "AbilitySystem/AttributeSet_Base.h"

#include "FunctionLibrary_Base.h"
#include "GameplayEffectExtension.h"
#include "GameplayTags_Base.h"
#include "Components/UI/UIComponent_Base.h"
#include "Components/UI/UIComponent_Player.h"
#include "Interfaces/PawnUIInterface.h"

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
	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}

	checkf(CachedPawnUIInterface.IsValid(), TEXT("%s didn't implement IPawnUIInterface"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	UUIComponent_Base* UIComponent = CachedPawnUIInterface->GetUIComponent();

	checkf(UIComponent, TEXT("Couldn't extract a UIComponent from %s"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);
		UIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
	}

	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage());
		SetCurrentRage(NewCurrentRage);
		if (GetCurrentRage() == GetMaxRage())
		{
			UFunctionLibrary_Base::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), GameplayTags_Base::Player_Status_Rage_Full);
		}
		else if (GetCurrentRage() == 0.f)
		{
			UFunctionLibrary_Base::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), GameplayTags_Base::Player_Status_Rage_None);
		}
		else
		{
			UFunctionLibrary_Base::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(), GameplayTags_Base::Player_Status_Rage_Full);
			UFunctionLibrary_Base::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(), GameplayTags_Base::Player_Status_Rage_None);
		}

		if (UUIComponent_Player* PlayerUIComponent = CachedPawnUIInterface->GetPlayerUIComponent())
		{
			PlayerUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage() / GetMaxRage());
		}
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();
		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);

		UIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());

		if (GetCurrentHealth() == 0.f)
		{
			UFunctionLibrary_Base::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), GameplayTags_Base::Shared_Status_Death);
		}
	}
}
