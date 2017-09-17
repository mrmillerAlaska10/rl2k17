#pragma once
class Navigator
{
public:
	Navigator();
	~Navigator();

	static int getDirection(int x, int y)
	{
		//North
		if (x == 0 && y == -1)
		{
			return 8;
		}
		//South
		if (x == 0 && y == 1)
		{
			return 2;
		}
		//East
		if (x == 1 && y == 0)
		{
			return 6;
		}
		//West
		if (x == -1 && y == 0)
		{
			return 4;
		}


		//south east
		if (x == 1 && y == 1)
		{
			return 3;
		}

		//north east
		if (x == 1 && y == -1)
		{
			return 9;
		}
		//south west
		if (x == -1 && y == 1)
		{
			return 1;
		}

		//north west
		if (x == -1 && y == -1)
		{
			return 7;
		}

		return 5;

		
		

	}

	static int getX(int direction)
	{
		int X;
		switch (direction)
		{
		case 1:
		case 4:
		case 7:
			X = -1;
			break;
		case 8:
		case 2:
			X = 0;
			break;
		case 9:
		case 6:
		case 3:
			X = 1;
			break;
		default:
			X = -1;
			break;
		}

		return X;
	}
	
	static int getY(int direction)
	{
		int Y;
		switch (direction)
		{
		case 7:
		case 8:
		case 9:
			Y = -1;
			break;
		case 4:
		case 6:
			Y = 0;
			break;
		case 1:
		case 2:
		case 3:
			Y = 1;
			break;
		default:
			Y = -1;
			break;
		}

		return Y;
	}
};

