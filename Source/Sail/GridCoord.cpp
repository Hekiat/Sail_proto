// Fill out your copyright notice in the Description page of Project Settings.


#include "GridCoord.h"


FORCEINLINE FHexCoord::FHexCoord()
{}


FORCEINLINE FHexCoord::FHexCoord(int32 InHexX, int32 InHexY, int32 InHexZ)
	: X(InHexX), Y(InHexY), Z(InHexZ)
{
}



FORCEINLINE FGridCoord::FGridCoord()
{}

FORCEINLINE FGridCoord::FGridCoord(const FHexCoord& hexCoord)
{

}

FORCEINLINE FGridCoord::FGridCoord(int32 InX, int32 InY)
	: X(InX), Y(InY)
{
}

FORCEINLINE FGridCoord FGridCoord::operator+(const FGridCoord& o) const
{
	return FGridCoord(X + o.X, Y + o.Y);
}

FORCEINLINE FGridCoord FGridCoord::operator-(const FGridCoord& o) const
{
	return FGridCoord(X - o.X, Y - o.Y);
}

FHexCoord FGridCoord::toHex() const
{
	auto x = X;
	auto z = Y - (X - (X % 2)) / 2;
	auto y = -x - z;
	return FHexCoord(x, y, z);
}