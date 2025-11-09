#include "GameModes/GameMode_Survival.h"

void AGameMode_Survival::BeginPlay()
{
	Super::BeginPlay();
}

void AGameMode_Survival::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AGameMode_Survival::SetCurrentGameModeState(EGameModeState InState)
{
	CurrentGameModeState = InState;
	OnGameModeStateChanged.Broadcast(CurrentGameModeState);
}
