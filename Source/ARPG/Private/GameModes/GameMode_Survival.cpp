#include "GameModes/GameMode_Survival.h"

#include "DebugHelper.h"
#include "NavigationSystem.h"
#include "Characters/Character_Enemy.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"

void AGameMode_Survival::BeginPlay()
{
	Super::BeginPlay();

	checkf(EnemyWaveSpawnerDataTable, TEXT("Forgot to assign a valid data table in survival game mode blueprint"));

	SetCurrentGameModeState(EGameModeState::WaitSpawnNewWave);

	TotalWavesToSpawn = EnemyWaveSpawnerDataTable->GetRowNames().Num();

	PreLoadNextWaveEnemies();
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
			CurrentSpawnedEnemiesCounter += TrySpawnWaveEnemies();

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
				PreLoadNextWaveEnemies();
			}
		}
	}
}

void AGameMode_Survival::OnEnemyDestroyed(AActor* DestroyedActor)
{
	CurrentSpawnedEnemiesCounter--;

	Debug::Print(FString::Printf(TEXT("CurrentSpawnedEnemiesCounter:%i, TotalSpawnedEnemiesThisWaveCounter:%i"), CurrentSpawnedEnemiesCounter, TotalSpawnedEnemiesThisWaveCounter));

	if (ShouldKeepSpawnEnemies())
	{
		CurrentSpawnedEnemiesCounter += TrySpawnWaveEnemies();
	}
	else if (CurrentSpawnedEnemiesCounter == 0)
	{
		TotalSpawnedEnemiesThisWaveCounter = 0;
		CurrentSpawnedEnemiesCounter = 0;

		SetCurrentGameModeState(EGameModeState::WaveCompleted);
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

void AGameMode_Survival::PreLoadNextWaveEnemies()
{
	if (HasFinishedAllWaves())
	{
		return;
	}

	PreLoadedEnemyClassMap.Empty();

	for (const FEnemyWaveSpawnerInfo& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerDefinitions)
	{
		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull()) continue;

		UAssetManager::GetStreamableManager().RequestAsyncLoad(
			SpawnerInfo.SoftEnemyClassToSpawn.ToSoftObjectPath(),
			FStreamableDelegate::CreateLambda(
				[SpawnerInfo,this]()
				{
					if (UClass* LoadedEnemyClass = SpawnerInfo.SoftEnemyClassToSpawn.Get())
					{
						PreLoadedEnemyClassMap.Emplace(SpawnerInfo.SoftEnemyClassToSpawn, LoadedEnemyClass);
					}
				}
			)
		);
	}
}

FEnemyWaveSpawnerTableRow* AGameMode_Survival::GetCurrentWaveSpawnerTableRow() const
{
	const FName RowName = FName(TEXT("Wave_") + FString::FromInt(CurrentWaveCount));
	FEnemyWaveSpawnerTableRow* FoundRow = EnemyWaveSpawnerDataTable->FindRow<FEnemyWaveSpawnerTableRow>(RowName, FString());
	checkf(FoundRow, TEXT("Could not find a valid row under the name %s in the data table"), *RowName.ToString());
	return FoundRow;
}

int32 AGameMode_Survival::TrySpawnWaveEnemies()
{
	if (TargetPointsArray.IsEmpty())
	{
		UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), TargetPointsArray);
	}

	checkf(!TargetPointsArray.IsEmpty(), TEXT("No valid target point found in level: %s for spawning enemies"), *GetWorld()->GetName());

	uint32 EnemiesSpawnedThisTime = 0;

	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (const FEnemyWaveSpawnerInfo& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerDefinitions)
	{
		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull())
			continue;

		const int32 NumToSpawn = FMath::RandRange(SpawnerInfo.MinPerSpawnCount, SpawnerInfo.MaxPerSpawnCount);
		UClass* LoadedEnemy = PreLoadedEnemyClassMap.FindChecked(SpawnerInfo.SoftEnemyClassToSpawn);
		for (int32 i = 0; i < NumToSpawn; i++)
		{
			const int32 RandomTargetPointIndex = FMath::RandRange(0, TargetPointsArray.Num() - 1);

			const FVector SpawnOrigin = TargetPointsArray[RandomTargetPointIndex]->GetActorLocation();
			FVector RandomLocation;
			UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(this, SpawnOrigin, RandomLocation, 400.f);
			RandomLocation += FVector(0.f, 0.f, 150.f);

			const FRotator SpawnRotation = TargetPointsArray[RandomTargetPointIndex]->GetActorForwardVector().ToOrientationRotator();

			if (ACharacter_Enemy* SpawnedEnemy = GetWorld()->SpawnActor<ACharacter_Enemy>(LoadedEnemy, RandomLocation, SpawnRotation, SpawnParam))
			{
				EnemiesSpawnedThisTime++;
				TotalSpawnedEnemiesThisWaveCounter++;
				SpawnedEnemy->OnDestroyed.AddUniqueDynamic(this, &ThisClass::OnEnemyDestroyed);
			}

			if (!ShouldKeepSpawnEnemies())
			{
				return EnemiesSpawnedThisTime;
			}
		}
	}

	return EnemiesSpawnedThisTime;
}

bool AGameMode_Survival::ShouldKeepSpawnEnemies() const
{
	return TotalSpawnedEnemiesThisWaveCounter < GetCurrentWaveSpawnerTableRow()->TotalEnemyToSpawnThisWave;
}

void AGameMode_Survival::RegisterSpawnedEnemies(const TArray<ACharacter_Enemy*>& InEnemiesToRegister)
{
	for (ACharacter_Enemy* SpawnedEnemy : InEnemiesToRegister)
	{
		if (SpawnedEnemy)
		{
			CurrentSpawnedEnemiesCounter++;
			SpawnedEnemy->OnDestroyed.AddUniqueDynamic(this,&ThisClass::OnEnemyDestroyed);
		}
	}
}
