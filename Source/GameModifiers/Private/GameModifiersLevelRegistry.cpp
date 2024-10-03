// Copyright (c) 2024 Anoho All rights reserved.

#include "GameModifiersLevelRegistry.h"

// Include headers in AssetRegistry module.
#include "AssetRegistry/IAssetRegistry.h"
#include "AssetRegistry/AssetRegistryModule.h"

#include "Kismet/KismetSystemLibrary.h"

FGameModifiersLevelOverride UGameModifiersLevelRegistry::GetLevelOverrideByName(FName Origin) const
{
	FName OriginLongPackageName = MakeLongPackageName(Origin);

	if (!LevelNameToLevelOverride.Contains(OriginLongPackageName))
	{
		return /*FGameModifiersLevelOverride*/
		{
			/*LongPackageName*/ Origin,
		};
	}

	return *LevelNameToLevelOverride.Find(OriginLongPackageName);
}

void UGameModifiersLevelRegistry::GetStreamLevelsByName(FName LevelName, TArray<FGameModifiersStreamLevel>& OutStreamLevels)
{
	OutStreamLevels.Empty();

	FName LevelLongPackageName = MakeLongPackageName(LevelName);

	if (LevelLongPackageName.IsNone())
	{
		return;
	}

	if (!LevelNameToStreamLevels.Contains(LevelLongPackageName))
	{
		return;
	}

	TArray<FGameModifiersStreamLevel>* RegisteredStreamLevels = LevelNameToStreamLevels.Find(LevelLongPackageName);

	for (const FGameModifiersStreamLevel& StreamLevel : *RegisteredStreamLevels)
	{
		OutStreamLevels.Emplace(StreamLevel);
	}
}

void UGameModifiersLevelRegistry::RegisterLevelOverrideByName(FName Origin, FName Override)
{
	FName OriginLongPackageName = MakeLongPackageName(Origin);
	FName OverrideLongPackageName = MakeLongPackageName(Override);

	if (OriginLongPackageName.IsNone() || OverrideLongPackageName.IsNone())
	{
		return;
	}

	FGameModifiersLevelOverride NewLevelOverride
	{
		/*LongPackageName*/ OverrideLongPackageName,
	};

	LevelNameToLevelOverride.Emplace(OriginLongPackageName, NewLevelOverride);
}

void UGameModifiersLevelRegistry::RegisterStreamLevelByName(FName LevelName, FName StreamLevelName)
{
	FName LevelLongPackageName = MakeLongPackageName(LevelName);

	if (LevelLongPackageName.IsNone())
	{
		return;
	}

	TArray<FGameModifiersStreamLevel>& RegisteredStreamLevels = LevelNameToStreamLevels.FindOrAdd(LevelLongPackageName);

	FName StreamLevelLongPackageName = MakeLongPackageName(StreamLevelName);

	if (LevelLongPackageName.IsNone())
	{
		return;
	}

	bool bHasStreamLevelRegistered = RegisteredStreamLevels.ContainsByPredicate([StreamLevelLongPackageName](const FGameModifiersStreamLevel& StreamLevel) { return StreamLevel.LongPackageName == StreamLevelLongPackageName; });

	if (bHasStreamLevelRegistered)
	{
		return;
	}

	FGameModifiersStreamLevel StreamLevel
	{
		/*LevelName*/ StreamLevelName
	};

	RegisteredStreamLevels.Emplace(StreamLevelLongPackageName);
}

void UGameModifiersLevelRegistry::UnregisterLevelOverrideByName(FName Origin)
{
	FName OriginLongPackageName = MakeLongPackageName(Origin);

	if (OriginLongPackageName.IsNone())
	{
		return;
	}

	LevelNameToLevelOverride.Remove(OriginLongPackageName);
}

void UGameModifiersLevelRegistry::UnregisterStreamLevelByName(FName LevelName, FName StreamLevelName)
{
	FName LevelLongPackageName = MakeLongPackageName(LevelName);

	TArray<FGameModifiersStreamLevel>* RegisteredStreamLevels = LevelNameToStreamLevels.Find(LevelLongPackageName);

	if (!RegisteredStreamLevels)
	{
		return;
	}

	FName StreamLevelLongPackageName = MakeLongPackageName(StreamLevelName);

	for (int I = 0; I < RegisteredStreamLevels->Num(); I++)
	{
		const FGameModifiersStreamLevel& StreamLevel = (*RegisteredStreamLevels)[I];

		if (StreamLevel.LongPackageName == StreamLevelLongPackageName)
		{
			RegisteredStreamLevels->RemoveAt(I);

			break;
		}
	}
}

/*
* レベル名から LongPackageName を生成する
*/
FName UGameModifiersLevelRegistry::MakeLongPackageName(const FName& LevelName)
{
	FName LongPackageName = NAME_None;

	// NOTE:この関数では LongPackageName に PIE の prefix を消去しないため、LevelName に PIE がついていた場合は NAME_None を返す
	// （呼び出し元の関数によっては WorldContextObject を取得できないため）	

	// NOTE: LevelName の変換について
	// 
	// ULevelStreamingDynamic::LoadLevelInstance 関数では渡された LevelName が ShortPackageName だった場合に
	// 以下のような処理で LongPackageName に変換している
	//
	// const FString PackagePath = FPackageName::GetLongPackagePath(Params.LongPackageName);
	// FString ShortPackageName = FPackageName::GetShortName(Params.LongPackageName);
	// （中略）
	// const FString OnDiskPackageName = PackagePath + TEXT("/") + ShortPackageName;
	// （中略）
	// StreamingLevel->PackageNameToLoad = FName(*OnDiskPackageName);
	// 
	// 引用元: https://github.com/EpicGames/UnrealEngine/blob/16dc333db3d6439c7f2886cf89db8907846c0e8a/Engine/Source/Runtime/Engine/Private/LevelStreaming.cpp#L2560

	IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get();
	FString ShortPackageNameStr = FPackageName::GetShortName(LevelName);
		
	FName ExistingPackageName = AssetRegistry.GetFirstPackageByName(ShortPackageNameStr);

	if (!ExistingPackageName.IsNone())
	{
		LongPackageName = FName(FPackageName::GetLongPackagePath(ExistingPackageName.ToString()) + TEXT("/") + ShortPackageNameStr);
	}

	return LongPackageName;
}
