#include "Characters/Character_Base.h"
#include "AbilitySystem/AbilitySystemComponent_Base.h"
#include "AbilitySystem/AttributeSet_Base.h"

ACharacter_Base::ACharacter_Base()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	CharacterASC = CreateDefaultSubobject<UAbilitySystemComponent_Base>(TEXT("CharacterAbilitySystemComponent"));
	CharacterAS = CreateDefaultSubobject<UAttributeSet_Base>(TEXT("CharacterAttributeSet"));
}

UAbilitySystemComponent* ACharacter_Base::GetAbilitySystemComponent() const
{
	return GetCharacterAbilitySystemComponent();
}

void ACharacter_Base::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (CharacterASC)
	{
		CharacterASC->InitAbilityActorInfo(this, this);

		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}
}
