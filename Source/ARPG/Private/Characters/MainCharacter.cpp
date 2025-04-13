#include "Characters/MainCharacter.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "AbilitySystem/MainAttributeSet.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	CharacterAbilitySystemComponent = CreateDefaultSubobject<UMainAbilitySystemComponent>(TEXT("CharacterAbilitySystemComponent"));
	CharacterAttributeSet = CreateDefaultSubobject<UMainAttributeSet>(TEXT("CharacterAttributeSet"));
}

UAbilitySystemComponent* AMainCharacter::GetAbilitySystemComponent() const
{
	return GetCharacterAbilitySystemComponent();
}

void AMainCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if(CharacterAbilitySystemComponent)
	{
		CharacterAbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}
