// Fill out your copyright notice in the Description page of Project Settings.


#include "GridCoord.h"

FORCEINLINE FSquareCoord::FSquareCoord()
{

}

FORCEINLINE FSquareCoord::FSquareCoord(int32 _X, int32 _Y)
	: X(_X), Y(_Y)
{

}

FHexCoord FSquareCoord::toHex() const
{
	auto x = X;
	auto z = Y - (X - (X % 2)) / 2;
	auto y = -x - z;
	return FHexCoord(x, y, z);
}

FORCEINLINE FString FSquareCoord::ToString() const
{
	return FString::Printf(TEXT("(%d, %d)"), X, Y);
}

FORCEINLINE FHexCoord::FHexCoord()
{}


FORCEINLINE FHexCoord::FHexCoord(int32 _HexX, int32 _HexY, int32 _HexZ)
	: X(_HexX), Y(_HexY), Z(_HexZ)
{
}

FORCEINLINE FString FHexCoord::ToString() const
{
	return FString::Printf(TEXT("(%d, %d, %d)"), X, Y, Z);
}

FORCEINLINE FSquareCoord FHexCoord::toSquare() const
{
	return FSquareCoord(-1, -1);
}


FORCEINLINE FGridCoord::FGridCoord()
{}

FORCEINLINE FGridCoord::FGridCoord(const FHexCoord& hc)
{
	HexCoord = hc;
	updateSquare();
}

FORCEINLINE FGridCoord::FGridCoord(const FSquareCoord& sc)
{
	SquareCoord = sc;
	updateHex();
}

FORCEINLINE FGridCoord::FGridCoord(const int32 _X, const int32 _Y)
	: SquareCoord(_X, _Y)
{
	updateHex();
}

FORCEINLINE FGridCoord::FGridCoord(const int32 _X, const int32 _Y, const int32 _Z)
	: HexCoord(_X, _Y, _Z)
{

}

FORCEINLINE FGridCoord FGridCoord::operator+(const FGridCoord& o) const
{
	return FGridCoord(SquareCoord.X + o.SquareCoord.X, SquareCoord.Y + o.SquareCoord.Y);
}

FORCEINLINE FGridCoord FGridCoord::operator-(const FGridCoord& o) const
{
	return FGridCoord(SquareCoord.X - o.SquareCoord.X, SquareCoord.Y - o.SquareCoord.Y);
}

FORCEINLINE void FGridCoord::setSquareCoord(const FSquareCoord& sc)
{
	SquareCoord = sc;

	updateHex();
}

FORCEINLINE void FGridCoord::setHexCoord(const FHexCoord& hc)
{
	HexCoord = hc;
	updateSquare();
}

FORCEINLINE FString FGridCoord::ToString() const
{
	return "[" + SquareCoord.ToString() + ", " + HexCoord.ToString() + "]";
}


void FGridCoord::updateSquare()
{
	SquareCoord = HexCoord.toSquare();
}

void FGridCoord::updateHex()
{
	HexCoord = SquareCoord.toHex();
}