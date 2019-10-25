// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "ObjectMacros.h"
#include "GridCoord.generated.h"


USTRUCT(BlueprintType)
struct SAIL_API FGridCoord
{
	GENERATED_USTRUCT_BODY()

	// Classic coord system
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GridCoord")
	int32 r;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GridCoord")
	int32 c;

	// Hex coord system
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GridCoord")
	int32 x;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GridCoord")
	int32 y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GridCoord")
	int32 z;

};