#include "FunctionLibrary_Base.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTags_Base.h"
#include "GenericTeamAgentInterface.h"
#include "AbilitySystem/AbilitySystemComponent_Base.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Types/CountdownAction.h"
#include "GameInstance_Base.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SaveGame_Base.h"

UAbilitySystemComponent_Base* UFunctionLibrary_Base::NativeGetASCFromActor(AActor* InActor)
{
	check(InActor);
	return CastChecked<UAbilitySystemComponent_Base>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}


void UFunctionLibrary_Base::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UAbilitySystemComponent_Base* ASC = NativeGetASCFromActor(InActor);
	if(!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UFunctionLibrary_Base::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UAbilitySystemComponent_Base* ASC = NativeGetASCFromActor(InActor);
	if(ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool UFunctionLibrary_Base::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UAbilitySystemComponent_Base* ASC = NativeGetASCFromActor(InActor);
	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UFunctionLibrary_Base::BP_DoesActorHaveTag(AActor* InActor, const FGameplayTag TagToCheck, EConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EConfirmType::Yes : EConfirmType::No;
}

///@brief Get Combat Comp
UCombatComponent_Base* UFunctionLibrary_Base::NativeGetCCFromActor(AActor* InActor)
{
	check(InActor);

	if(IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetCombatComponent();
	}

	return nullptr;
}

UCombatComponent_Base* UFunctionLibrary_Base::BP_GetCombatComponentFromActor(AActor* InActor, EValidType& OutValidType)
{
	UCombatComponent_Base* CombatComponent = NativeGetCCFromActor(InActor);
	OutValidType = CombatComponent ? EValidType::Valid : EValidType::Invalid;
	return CombatComponent;
}

bool UFunctionLibrary_Base::IsTargetPawnHostile(const APawn* QueryPawn, const APawn* TargetPawn)
{
	check(QueryPawn&&TargetPawn);
	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if(QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}
	return false;
}

float UFunctionLibrary_Base::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

// ??
FGameplayTag UFunctionLibrary_Base::ComputeHitReactDirectionTag(const AActor* InAttacker, const AActor* InVictim, float& OutAngleDifference)
{
	check(InAttacker&& InVictim);
	const FVector VictimForward = InVictim->GetActorForwardVector();
	const FVector VictimToAttackerNormalized = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(VictimForward, VictimToAttackerNormalized);
	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossRest = FVector::CrossProduct(VictimForward, VictimToAttackerNormalized);
	if(CrossRest.Z < 0.f)
	{
		OutAngleDifference *= -1.f;
	}

	if(OutAngleDifference >= -45.f && OutAngleDifference <= 45.f)
	{
		return GameplayTags_Base::Shared_Status_HitReact_Front;
	}
	if(OutAngleDifference < -45.f && OutAngleDifference >= -135.f)
	{
		return GameplayTags_Base::Shared_Status_HitReact_Left;
	}
	if(OutAngleDifference > 45.f && OutAngleDifference <= 135.f)
	{
		return GameplayTags_Base::Shared_Status_HitReact_Right;
	}
	if(OutAngleDifference < -135.f || OutAngleDifference > 135.f)
	{
		return GameplayTags_Base::Shared_Status_HitReact_Back;
	}

	return GameplayTags_Base::Shared_Status_HitReact_Front;
}

bool UFunctionLibrary_Base::IsValidBlock(const AActor* InAttacker, const AActor* InDefender)
{
	check(InAttacker&& InDefender);
	const float DotResult = FVector::DotProduct(InAttacker->GetActorForwardVector(), InDefender->GetActorForwardVector()); // 0->1
	return DotResult < -0.1f;
}

bool UFunctionLibrary_Base::ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	UAbilitySystemComponent_Base* SourceASC = NativeGetASCFromActor(InInstigator);
	UAbilitySystemComponent_Base* TargetASC = NativeGetASCFromActor(InTargetActor);
	FActiveGameplayEffectHandle   ActiveGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);
	return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}

void UFunctionLibrary_Base::CountDown(const UObject*        WorldContextObject, float TotalTime, float UpdateInterval, float& OutRemainingTime,
                                      ECountdownActionInput CountdownInput,
                                      UPARAM(DisplayName="Output")
                                      ECountdownActionOutput& CountdownOutput,
                                      FLatentActionInfo       LatenInfo)
{
	UWorld* World = nullptr;
	if(GEngine)
	{
		World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	}

	if(!World)
	{
		return;
	}

	FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
	FCountdownAction*     FoundAction = LatentActionManager.FindExistingAction<FCountdownAction>(LatenInfo.CallbackTarget, LatenInfo.UUID);
	if(CountdownInput == ECountdownActionInput::Start)
	{
		if(!FoundAction)
		{
			LatentActionManager.AddNewAction(
				LatenInfo.CallbackTarget,
				LatenInfo.UUID,
				new FCountdownAction(TotalTime, UpdateInterval, OutRemainingTime, CountdownOutput, LatenInfo)
			);
		}
	}

	if(CountdownInput == ECountdownActionInput::Cancel)
	{
		if(FoundAction)
		{
			FoundAction->CancelAction();
		}
	}
}

UGameInstance_Base* UFunctionLibrary_Base::GetGameInstance(const UObject* WorldContextObject)
{
	if(GEngine)
	{
		if(UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			return World->GetGameInstance<UGameInstance_Base>();
		}
	}

	return nullptr;
}

void UFunctionLibrary_Base::ToggleInputMode(const UObject* WorldContextObject, EInputMode InInputMode)
{
	APlayerController* PlayerController = nullptr;

	if(GEngine)
	{
		if(UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			PlayerController = World->GetFirstPlayerController();
		}
	}

	if(!PlayerController) return;

	FInputModeGameOnly GameOnlyMode;
	FInputModeUIOnly   UIOnlyMode;

	switch(InInputMode)
	{
	case EInputMode::GameOnly:
		PlayerController->SetInputMode(GameOnlyMode);
		PlayerController->bShowMouseCursor = false;
		break;
	case EInputMode::UIOnly:
		PlayerController->SetInputMode(UIOnlyMode);
		PlayerController->bShowMouseCursor = true;
		break;
	default:
		break;
	}
}

void UFunctionLibrary_Base::SaveCurrentGameDifficulty(EGameDifficulty InDifficultyToSave)
{
	USaveGame* SaveGameObject = UGameplayStatics::CreateSaveGameObject(USaveGame_Base::StaticClass());

	if(USaveGame_Base* SaveGame_Base = Cast<USaveGame_Base>(SaveGameObject))
	{
		SaveGame_Base->SavedCurrentGameDifficulty = InDifficultyToSave;

		// ! asynchronously, acceptable to save small datas
		const bool bWasSaved = UGameplayStatics::SaveGameToSlot(SaveGame_Base, GameplayTags_Base::GameData_SaveGame_Slot_1.GetTag().ToString(), 0);
	}
}

bool UFunctionLibrary_Base::TryLoadSavedGameDifficulty(EGameDifficulty& OutSavedDifficulty)
{
	if(UGameplayStatics::DoesSaveGameExist(GameplayTags_Base::GameData_SaveGame_Slot_1.GetTag().ToString(), 0))
	{
		USaveGame* SaveGameObject = UGameplayStatics::LoadGameFromSlot(GameplayTags_Base::GameData_SaveGame_Slot_1.GetTag().ToString(), 0);

		if(USaveGame_Base* SaveGame_Base = Cast<USaveGame_Base>(SaveGameObject))
		{
			OutSavedDifficulty = SaveGame_Base->SavedCurrentGameDifficulty;

			return true;
		}
	}

	return false;
}
