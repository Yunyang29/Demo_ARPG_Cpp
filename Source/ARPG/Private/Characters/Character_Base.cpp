#include "Characters/Character_Base.h"

#include "AbilitySystem/AbilitySystemComponent_Base.h"
#include "AbilitySystem/AttributeSet_Base.h"
#include "MotionWarpingComponent.h"

ACharacter_Base::ACharacter_Base()
{
	PrimaryActorTick.bCanEverTick = false; // 禁用Tick
	PrimaryActorTick.bStartWithTickEnabled = false; // 禁用Tick

	GetMesh()->bReceivesDecals = false; // 禁用接收Decal

	ASC = CreateDefaultSubobject<UAbilitySystemComponent_Base>(TEXT("CharAbilitySystemComp"));
	AS = CreateDefaultSubobject<UAttributeSet_Base>(TEXT("CharAttributeSet"));
	MWC = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

UAbilitySystemComponent* ACharacter_Base::GetAbilitySystemComponent() const
{
	return GetCharacterAbilitySystemComponent();
}

UCombatComponent_Base* ACharacter_Base::GetCombatComponent() const
{
	return nullptr;
}

UUIComponent_Base* ACharacter_Base::GetUIComponent() const
{
	return nullptr;
}

/// @brief 当角色被某个控制器（如玩家控制器或 AI 控制器）控制时调用
/// @param NewController
void ACharacter_Base::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (ASC)
	{
		// 初始化能力系统组件的角色信息
		ASC->InitAbilityActorInfo(this, this);
		ensureMsgf(!StartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}
}
