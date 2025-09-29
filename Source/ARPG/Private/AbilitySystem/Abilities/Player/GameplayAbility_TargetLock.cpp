#include "AbilitySystem/Abilities/Player/GameplayAbility_TargetLock.h"

#include "DebugHelper.h"
#include "FunctionLibrary_Base.h"
#include "GameplayTags_Base.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Characters/Character_Player.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Controllers/PlayerController_Base.h"
#include "Kismet/KismetMathLibrary.h"
#include "Widgets/Widget_Base.h"

void UGameplayAbility_TargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	TryLockOnTarget();
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGameplayAbility_TargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	CleanUp();
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGameplayAbility_TargetLock::OnTargetLockTick(float DeltaTime)
{
	if (!CurLockedActor ||
		UFunctionLibrary_Base::NativeDoesActorHaveTag(CurLockedActor, GameplayTags_Base::Shared_Status_Death) ||
		UFunctionLibrary_Base::NativeDoesActorHaveTag(GetPlayerCharacterFromActorInfo(), GameplayTags_Base::Shared_Status_Death)
	)
	{
		CancelTargetLockAbility();
		return;
	}

	SetTargetLockWidgetPosition();
	const bool bShouldOverrideRotation =
		!UFunctionLibrary_Base::NativeDoesActorHaveTag(GetPlayerCharacterFromActorInfo(), GameplayTags_Base::Player_Status_Rolling) &&
		!UFunctionLibrary_Base::NativeDoesActorHaveTag(GetPlayerCharacterFromActorInfo(), GameplayTags_Base::Player_Status_Blocking);

	// ?
	if (bShouldOverrideRotation)
	{
		const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetPlayerCharacterFromActorInfo()->GetActorLocation(), CurLockedActor->GetActorLocation());
		const FRotator CurControlRot = GetPlayerControllerFromActorInfo()->GetControlRotation();
		const FRotator TargetRot = FMath::RInterpTo(CurControlRot, LookAtRot, DeltaTime, TargetLockRotationInterpSpeed);

		GetPlayerControllerFromActorInfo()->SetControlRotation(FRotator(TargetRot.Pitch, TargetRot.Yaw, 0.f));
		GetPlayerCharacterFromActorInfo()->SetActorRotation(FRotator(0.f, TargetRot.Yaw, 0.f));
	}
}

AActor* UGameplayAbility_TargetLock::GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors)
{
	float ClosestDistance = 0.f;
	return UGameplayStatics::FindNearestActor(GetPlayerCharacterFromActorInfo()->GetActorLocation(), InAvailableActors, ClosestDistance);
}

void UGameplayAbility_TargetLock::DrawTargetLockWidget()
{
	if (!DrawnTargetLockWidget)
	{
		checkf(TargetLockWidgetClass, TEXT("Forget to assign a valid widget class in Blueprint"));

		DrawnTargetLockWidget = CreateWidget<UWidget_Base>(GetPlayerControllerFromActorInfo(), TargetLockWidgetClass);

		check(DrawnTargetLockWidget);

		DrawnTargetLockWidget->AddToViewport();
	}
}

void UGameplayAbility_TargetLock::SetTargetLockWidgetPosition()
{
	if (!DrawnTargetLockWidget || !CurLockedActor)
	{
		CancelTargetLockAbility();
		return;
	}

	FVector2D ScreenPosition;
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(GetPlayerControllerFromActorInfo(), CurLockedActor->GetActorLocation(), ScreenPosition, true);

	if (TargetLockWidgetSize == FVector2D::ZeroVector)
	{
		DrawnTargetLockWidget->WidgetTree->ForEachWidget(
			[this](UWidget* FoundWidget)
			{
				if (USizeBox* FoundSizeBox = Cast<USizeBox>(FoundWidget))
				{
					TargetLockWidgetSize.X = FoundSizeBox->GetWidthOverride();
					TargetLockWidgetSize.Y = FoundSizeBox->GetHeightOverride();
				}
			});
	}

	ScreenPosition -= (TargetLockWidgetSize / 2.f);
	DrawnTargetLockWidget->SetPositionInViewport(ScreenPosition, false);
}


void UGameplayAbility_TargetLock::TryLockOnTarget()
{
	GetAvailableActorsToLock();

	if (AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}

	CurLockedActor = GetNearestTargetFromAvailableActors(AvailableActorsToLock);

	if (CurLockedActor)
	{
		DrawTargetLockWidget();
		SetTargetLockWidgetPosition();
	}
	else
	{
		CancelTargetLockAbility();
	}
}


void UGameplayAbility_TargetLock::CancelTargetLockAbility()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);;
}

void UGameplayAbility_TargetLock::CleanUp()
{
	AvailableActorsToLock.Empty();

	CurLockedActor = nullptr;

	if (DrawnTargetLockWidget)
	{
		DrawnTargetLockWidget->RemoveFromParent();
	}
	DrawnTargetLockWidget = nullptr;
	TargetLockWidgetSize = FVector2D::ZeroVector;
}

void UGameplayAbility_TargetLock::GetAvailableActorsToLock()
{
	TArray<FHitResult> BoxTraceHits;
	ACharacter_Player* Player = GetPlayerCharacterFromActorInfo();
	UKismetSystemLibrary::BoxTraceMultiForObjects(
		Player,
		Player->GetActorLocation(),
		Player->GetActorLocation() + Player->GetActorForwardVector() * BoxTraceDistance,
		BoxTraceSize / 2.f,
		GetPlayerCharacterFromActorInfo()->GetActorForwardVector().ToOrientationRotator(),
		BoxTraceChannel,
		false,
		TArray<AActor*>(),
		bShowPersistentDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		BoxTraceHits,
		true
	);

	for (const FHitResult& HitResult : BoxTraceHits)
	{
		if (AActor* Actor = HitResult.GetActor())
		{
			if (Actor != Player)
			{
				AvailableActorsToLock.AddUnique(Actor);
			}
		}
	}
}
