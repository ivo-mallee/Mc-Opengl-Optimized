#pragma once


//class that holds a boolean for every side of a cube (6 in total) and one Integer 
class SIDES {       
public:             
	bool LEFT = false;
	bool RIGHT = false;
	bool TOP = false;
	bool BOTTOM = false;
	bool FRONT = false;
	bool BACK = false;
	int NUMBER = 0;
};

//returns texture Settings when given block id (might possibly return more in future)
void getTextureData(int ID, int& minX, int& minY) 
{
	switch (ID)
	{
	case 1:
		minX = 1; minY = 14; //dirt
		break;
	case 2:
		minX = 0; minY = 14; //stone
		break;
	case 3:
		minX = 2; minY = 14; //grass
	break;

	case 4:
		minX = 13; minY = 14; //water
	break;
	case 5:
		minX = 1; minY = 10; //SNOW
	break;









	default:
		break;
	}


}