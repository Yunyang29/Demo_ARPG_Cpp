#include "Characters/Character_Base.h"
#include "AbilitySystem/AbilitySystemComponent_Base.h"
#include "AbilitySystem/AttributeSet_Base.h"

ACharacter_Base::ACharacter_Base()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	ASC = CreateDefaultSubobject<UAbilitySystemComponent_Base>(TEXT("CharAbilitySystemComp"));
	AS = CreateDefaultSubobject<UAttributeSet_Base>(TEXT("CharAttributeSet"));
}

UAbilitySystemComponent* ACharacter_Base::GetAbilitySystemComponent() const
{
	return GetCharacterAbilitySystemComponent();
}

void ACharacter_Base::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (ASC)
	{
		ASC->InitAbilityActorInfo(this, this);

		ensureMsgf(!StartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}
}
