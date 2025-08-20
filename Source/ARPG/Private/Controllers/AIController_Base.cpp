#include "Controllers/AIController_Base.h"

#include "DebugHelper.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AAIController_Base::AAIController_Base(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent")) // ?
{
	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("SenseConfig_Sight");
	AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
	AISenseConfig_Sight->SightRadius = 5000.f;
	AISenseConfig_Sight->LoseSightRadius = 0.f;
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 360.f;

	SelfPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComp");
	SelfPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
	SelfPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	SelfPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnPerceptionUpdated);

	SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type AAIController_Base::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn*                      PawnToCheck = Cast<const APawn>(&Other);
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(PawnToCheck->GetController());
	if(OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() < GetGenericTeamId())
	{
		return ETeamAttitude::Hostile;
	}
	return ETeamAttitude::Friendly;
}

void AAIController_Base::BeginPlay()
{
	Super::BeginPlay();

	if(UCrowdFollowingComponent* CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		CrowdComp->SetCrowdSimulationState(bEnableDetourCrowdAvoidance ? ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled);
		switch(DetourCrowdAvoidQuality)
		{
		case 1:
			CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);
			break;
		case 2:
			CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);
			break;
		case 3:
			CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);
			break;
		case 4:
			CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
			break;
		default:
			break;
		}
		CrowdComp->SetAvoidanceGroup(1);
		CrowdComp->SetGroupsToAvoid(1);
		CrowdComp->SetCrowdCollisionQueryRange(CollisionQueryRange);
	}
}

void AAIController_Base::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if(UBlackboardComponent* BlackboardComp = GetBlackboardComponent())
	{
		if(!BlackboardComp->GetValueAsObject(FName("TargetActor")))
		{
			if(Stimulus.WasSuccessfullySensed() && Actor)
			{
				BlackboardComp->SetValueAsObject(FName("TargetActor"), Actor);
			}
		}
	}
}
