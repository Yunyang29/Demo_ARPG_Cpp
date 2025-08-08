#include "DataAssets/StartUp/DataAsset_StartUp.h"
#include "AbilitySystem/AbilitySystemComponent_Base.h"
#include "AbilitySystem/Abilities/GameplayAbility_Base.h"

/// @brief 将预设的能力赋予指定的能力系统组件(ASC)
/// @param InASCToGive 目标能力系统组件
/// @param ApplyLevel 应用的能力等级，默认为1
void UDataAsset_StartUp::GiveToAbilitySystemComponent(UAbilitySystemComponent_Base* InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive); // 确保传入的ASC不为空

	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel); // 赋予被动或反应型能力
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel); // 赋予主动能力

	if(!StartUpGameplayEffects.IsEmpty())
	{
		for(const TSubclassOf<UGameplayEffect>& EffectClass : StartUpGameplayEffects)
		{
			if(!EffectClass) continue;

			UGameplayEffect* EffectCDO = EffectClass->GetDefaultObject<UGameplayEffect>();
			InASCToGive->ApplyGameplayEffectToSelf(EffectCDO, ApplyLevel, InASCToGive->MakeEffectContext());
		}
	}
}

/// @brief 辅助方法，实际执行赋予能力的逻辑
/// @param InAbilitiesToGive 要赋予的能力类数组
/// @param InASCToGive 目标能力系统组件
/// @param ApplyLevel 应用的能力等级
void UDataAsset_StartUp::GrantAbilities(const TArray<TSubclassOf<UGameplayAbility_Base>>& InAbilitiesToGive, UAbilitySystemComponent_Base* InASCToGive, int32 ApplyLevel)
{
	if(InAbilitiesToGive.IsEmpty())
	{
		return;
	}

	for(const TSubclassOf<UGameplayAbility_Base>& Ability : InAbilitiesToGive)
	{
		if(!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability); // 创建能力规格
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor(); // 设置能力来源对象为当前角色
		AbilitySpec.Level = ApplyLevel; // 设置能力等级
		InASCToGive->GiveAbility(AbilitySpec); // 将能力规格赋予ASC
	}
}
