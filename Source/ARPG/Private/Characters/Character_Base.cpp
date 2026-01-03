#include "Characters/Character_Base.h"

#include "AbilitySystem/AbilitySystemComponent_Base.h"
#include "AbilitySystem/AttributeSet_Base.h"
#include "MotionWarpingComponent.h"

ACharacter_Base::ACharacter_Base()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

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

void ACharacter_Base::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if(ASC)
	{
		ASC->InitAbilityActorInfo(this, this);
		ensureMsgf(!StartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}
}
