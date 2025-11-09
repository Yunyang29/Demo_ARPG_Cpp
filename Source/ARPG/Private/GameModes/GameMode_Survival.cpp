#include "GameModes/GameMode_Survival.h"

void AGameMode_Survival::BeginPlay()
{
	Super::BeginPlay();

	checkf(EnemyWaveSpawnerDataTable, TEXT("Forgot to assign a valid datat table in survial game mode blueprint"));

	SetCurrentGameModeState(EGameModeState::WaitSpawnNewWave);

	TotalWavesToSpawn = EnemyWaveSpawnerDataTable->GetRowNames().Num();
}

void AGameMode_Survival::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TimePassedSinceStart += DeltaSeconds;

	if (CurrentGameModeState == EGameModeState::WaitSpawnNewWave)
	{
		if (TimePassedSinceStart >= WaitTimeToSpawnNewWave)
		{
			TimePassedSinceStart = 0.f;

			SetCurrentGameModeState(EGameModeState::SpawningNewWave);
		}
	}

	if (CurrentGameModeState == EGameModeState::SpawningNewWave)
	{
		if (TimePassedSinceStart >= DelayTimeToSpawnEnemies)
		{
			//TODO:Handle spawn new enemies

			TimePassedSinceStart = 0.f;

			SetCurrentGameModeState(EGameModeState::InProgress);
		}
	}

	if (CurrentGameModeState == EGameModeState::WaveCompleted)
	{
		if (TimePassedSinceStart >= WaitTimeToWaveCompleted)
		{
			TimePassedSinceStart = 0.f;

			CurrentWaveCount++;

			if (HasFinishedAllWaves())
			{
				SetCurrentGameModeState(EGameModeState::AllWavesDone);
			}
			else
			{
				SetCurrentGameModeState(EGameModeState::WaitSpawnNewWave);
			}
		}
	}
}

void AGameMode_Survival::SetCurrentGameModeState(EGameModeState InState)
{
	CurrentGameModeState = InState;
	OnGameModeStateChanged.Broadcast(CurrentGameModeState);
}

bool AGameMode_Survival::HasFinishedAllWaves() const
{
	return CurrentWaveCount > TotalWavesToSpawn;
}
