#pragma once
#include <random>
#include <vector>
#include <iostream>
#include <string>
namespace
{
	std::random_device rd;
	std::mt19937 mt(rd());

	int randomInt(int exclusiveMax)
	{
		std::uniform_int_distribution<> dist(0, exclusiveMax - 1);
		return dist(mt);
	}

	int randomInt(int min, int max) // inclusive min/max
	{
		std::uniform_int_distribution<> dist(0, max - min);
		return dist(mt) + min;
	}

	bool randomBool(double probability = 0.5)
	{
		std::bernoulli_distribution dist(probability);
		return dist(mt);
	}
}

struct Rect
{
	int x, y;
	int width, height;
};

class Dungeon
{
public:
	enum Tile
	{
		Unused = ' ',
		Floor = '.',
		Corridor = ',',
		Wall = '#',
		ClosedDoor = '+',
		OpenDoor = '-',
		UpStairs = '<',
		DownStairs = '>'
	};

	enum Direction
	{
		North,
		South,
		West,
		East,
		DirectionCount
	};

public:
	Dungeon(int width, int height)
		: _width(width)
		, _height(height)
		, _tiles(width * height, Unused)
		, _rooms()
		, _exits()
	{
	}

	void generate(int maxFeatures);
	void print();

	std::string * Export();
	

private:
	char getTile(int x, int y);

	void setTile(int x, int y, char tile);

	bool createFeature();

	bool createFeature(int x, int y, Direction dir);

	bool makeRoom(int x, int y, Direction dir, bool firstRoom = false);

	bool makeCorridor(int x, int y, Direction dir);

	bool placeRect(const Rect& rect, char tile);

	bool placeObject(char tile);

private:
	int _width, _height;
	std::vector<char> _tiles;
	std::vector<Rect> _rooms; // rooms for place stairs or monsters
	std::vector<Rect> _exits; // 4 sides of rooms or corridors
};
