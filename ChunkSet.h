#pragma once
#include "Chunk.h"
#include "worldGeneration.h"

//set of chunks 32x32 1024 in total 
class ChunkSet {


	//converts 4,8,4,4,4,8 bit value's into a singular integer
	unsigned int  ConvertTo(unsigned char X, unsigned char Y, unsigned char Z, unsigned char TX, unsigned char TY, unsigned char LightLevel)
	{
		unsigned int T = Y | X << 8 | Z << 12 | TX << 16 | TY << 20 | LightLevel << 24;





		return T;
	} 
	
	
		//adds the vertices and indices to referenced arrays. takes a 4,8,4 bit value, and then a SIDES object which constains the sides to be added
	void AddCube(unsigned char Xoffset, unsigned char Yoffset, unsigned char Zoffset, SIDES TEMP, int TextureId, GLuint(&indices)[300000], GLuint(&vertices)[1572864])
	{
		int MinX = 0;
		int MinY = 0;
		int MaxX = 0;
		int MaxY = 0;


		getTextureData(TextureId, MinX, MinY);

		unsigned char LightLevel;

		MaxY = MinY + 1;
		MaxX = MinX + 1;

		unsigned char SideLevel = 2;

		LightLevel = SideLevel;
		if (TEMP.FRONT == false) {
			vertices[this->VOffset + 0] = this->ConvertTo(0 + Xoffset, 0 + Yoffset, 1 + Zoffset, MinX, MinY, LightLevel); //FRONT
			vertices[this->VOffset + 1] = this->ConvertTo(1 + Xoffset, 0 + Yoffset, 1 + Zoffset, MaxX, MinY, LightLevel);
			vertices[this->VOffset + 2] = this->ConvertTo(0 + Xoffset, 1 + Yoffset, 1 + Zoffset, MinX, MaxY, LightLevel);
			vertices[this->VOffset + 3] = this->ConvertTo(1 + Xoffset, 1 + Yoffset, 1 + Zoffset, MaxX, MaxY, LightLevel);
			indices[this->IOffset + 0] = this->VOffset + 0;
			indices[this->IOffset + 1] = this->VOffset + 1;
			indices[this->IOffset + 2] = this->VOffset + 3;
			indices[this->IOffset + 3] = this->VOffset + 0;
			indices[this->IOffset + 4] = this->VOffset + 3;
			indices[this->IOffset + 5] = this->VOffset + 2;
			this->VOffset += 4;
			this->IOffset += 6;
		}

		LightLevel = 3;
		if (TEMP.BOTTOM == false) {
			vertices[this->VOffset + 0] = this->ConvertTo(0 + Xoffset, 0 + Yoffset, 0 + Zoffset, MinX, MinY, LightLevel); //bottom
			vertices[this->VOffset + 1] = this->ConvertTo(1 + Xoffset, 0 + Yoffset, 0 + Zoffset, MaxX, MinY, LightLevel);
			vertices[this->VOffset + 2] = this->ConvertTo(0 + Xoffset, 0 + Yoffset, 1 + Zoffset, MinX, MaxY, LightLevel);
			vertices[this->VOffset + 3] = this->ConvertTo(1 + Xoffset, 0 + Yoffset, 1 + Zoffset, MaxX, MaxY, LightLevel);
			indices[this->IOffset + 0] = this->VOffset + 0;
			indices[this->IOffset + 1] = this->VOffset + 1;
			indices[this->IOffset + 2] = this->VOffset + 3;
			indices[this->IOffset + 3] = this->VOffset + 0;
			indices[this->IOffset + 4] = this->VOffset + 3;
			indices[this->IOffset + 5] = this->VOffset + 2;
			this->VOffset += 4;
			this->IOffset += 6;
		}

		LightLevel = SideLevel;
		if (TEMP.BACK == false) {
			vertices[this->VOffset + 0] = this->ConvertTo(0 + Xoffset, 1 + Yoffset, 0 + Zoffset, MaxX, MaxY, LightLevel); //BACK
			vertices[this->VOffset + 1] = this->ConvertTo(1 + Xoffset, 1 + Yoffset, 0 + Zoffset, MinX, MaxY, LightLevel);
			vertices[this->VOffset + 2] = this->ConvertTo(0 + Xoffset, 0 + Yoffset, 0 + Zoffset, MaxX, MinY, LightLevel);
			vertices[this->VOffset + 3] = this->ConvertTo(1 + Xoffset, 0 + Yoffset, 0 + Zoffset, MinX, MinY, LightLevel);
			indices[this->IOffset + 0] = this->VOffset + 0;
			indices[this->IOffset + 1] = this->VOffset + 1;
			indices[this->IOffset + 2] = this->VOffset + 3;
			indices[this->IOffset + 3] = this->VOffset + 0;
			indices[this->IOffset + 4] = this->VOffset + 3;
			indices[this->IOffset + 5] = this->VOffset + 2;
			this->VOffset += 4;
			this->IOffset += 6;
		}
		LightLevel = 1;
		if (TEMP.TOP == false) {
			vertices[this->VOffset + 0] = this->ConvertTo(1 + Xoffset, 1 + Yoffset, 0 + Zoffset, MaxX, MaxY, LightLevel); //TOP
			vertices[this->VOffset + 1] = this->ConvertTo(0 + Xoffset, 1 + Yoffset, 0 + Zoffset, MinX, MaxY, LightLevel);
			vertices[this->VOffset + 2] = this->ConvertTo(1 + Xoffset, 1 + Yoffset, 1 + Zoffset, MaxX, MinY, LightLevel);
			vertices[this->VOffset + 3] = this->ConvertTo(0 + Xoffset, 1 + Yoffset, 1 + Zoffset, MinX, MinY, LightLevel);
			indices[this->IOffset + 0] = this->VOffset + 0;
			indices[this->IOffset + 1] = this->VOffset + 1;
			indices[this->IOffset + 2] = this->VOffset + 3;
			indices[this->IOffset + 3] = this->VOffset + 0;
			indices[this->IOffset + 4] = this->VOffset + 3;
			indices[this->IOffset + 5] = this->VOffset + 2;
			this->VOffset += 4;
			this->IOffset += 6;
		}

		LightLevel = SideLevel;
		if (TEMP.RIGHT == false) {
			vertices[this->VOffset + 0] = this->ConvertTo(1 + Xoffset, 0 + Yoffset, 1 + Zoffset, MinX, MinY, LightLevel); //right
			vertices[this->VOffset + 1] = this->ConvertTo(1 + Xoffset, 0 + Yoffset, 0 + Zoffset, MaxX, MinY, LightLevel);
			vertices[this->VOffset + 2] = this->ConvertTo(1 + Xoffset, 1 + Yoffset, 1 + Zoffset, MinX, MaxY, LightLevel);
			vertices[this->VOffset + 3] = this->ConvertTo(1 + Xoffset, 1 + Yoffset, 0 + Zoffset, MaxX, MaxY, LightLevel);
			indices[this->IOffset + 0] = this->VOffset + 0;
			indices[this->IOffset + 1] = this->VOffset + 1;
			indices[this->IOffset + 2] = this->VOffset + 3;
			indices[this->IOffset + 3] = this->VOffset + 0;
			indices[this->IOffset + 4] = this->VOffset + 3;
			indices[this->IOffset + 5] = this->VOffset + 2;
			this->VOffset += 4;
			this->IOffset += 6;
		}
		LightLevel = SideLevel;
		if (TEMP.LEFT == false) {
			vertices[this->VOffset + 0] = this->ConvertTo(0 + Xoffset, 0 + Yoffset, 1 + Zoffset, MaxX, MinY, LightLevel); //(Left Still has problem with culling needs FIX)
			vertices[this->VOffset + 1] = this->ConvertTo(0 + Xoffset, 0 + Yoffset, 0 + Zoffset, MinX, MinY, LightLevel);
			vertices[this->VOffset + 2] = this->ConvertTo(0 + Xoffset, 1 + Yoffset, 1 + Zoffset, MaxX, MaxY, LightLevel);
			vertices[this->VOffset + 3] = this->ConvertTo(0 + Xoffset, 1 + Yoffset, 0 + Zoffset, MinX, MaxY, LightLevel);
			indices[this->IOffset + 0] = this->VOffset + 0;
			indices[this->IOffset + 1] = this->VOffset + 1;
			indices[this->IOffset + 2] = this->VOffset + 3;
			indices[this->IOffset + 3] = this->VOffset + 0;
			indices[this->IOffset + 4] = this->VOffset + 3;
			indices[this->IOffset + 5] = this->VOffset + 2;
			this->VOffset += 4;
			this->IOffset += 6;
		}
	}


	//takes a 4,8,4 bit value and a reference to a chunk object. and then returns which sides contain a another cube
	SIDES checkburen(int CX, int CY, int CZ, Chunk& TARGET)
	{
		int buren = 0;
		int X = 0;
		int Y = 0;
		int Z = 0;

		SIDES TEMP;
		if (CX != 0) { if (TARGET.ChunkData[CX - 1][CY][CZ] != 0) { buren++; TEMP.LEFT = true; } }  //if there is a cube on the left
		if (CX == 0 && TARGET.LeftChunkNeighbhor) { if (TARGET.LeftChunk->ChunkData[14][CY][CZ] != 0) { buren++; TEMP.LEFT = true; } }


		if (CX != 14) { if (TARGET.ChunkData[CX + 1][CY][CZ] != 0) { buren++; TEMP.RIGHT = true; } }  //if there is a cube on the right
		if (CX == 14 && TARGET.RightChunkNeighbhor) { if (TARGET.RightChunk->ChunkData[0][CY][CZ] != 0) { buren++; TEMP.RIGHT = true; } }


		if (CY != 0) { if (TARGET.ChunkData[CX][CY - 1][CZ] != 0) { buren++; TEMP.BOTTOM = true; } }  //if there is a cube on the bottom
		if (CY != 255) { if (TARGET.ChunkData[CX][CY + 1][CZ] != 0) { buren++; TEMP.TOP = true; } }  //if there is a cube on the top


		if (CZ != 0) { if (TARGET.ChunkData[CX][CY][CZ - 1] != 0) { buren++; TEMP.BACK = true; } }  //if there is a cube on the back
		if (CZ == 0 && TARGET.BackChunkNeighbhor) { if (TARGET.BackChunk->ChunkData[CX][CY][14] != 0) { buren++; TEMP.BACK = true; } }

		if (CZ != 14) { if (TARGET.ChunkData[CX][CY][CZ + 1] != 0) { buren++; TEMP.FRONT = true; } }  //if there is a cube on the front
		if (CZ == 14 && TARGET.FrontChunkNeighbhor) { if (TARGET.FrontChunk->ChunkData[CX][CY][0] != 0) { buren++; TEMP.FRONT = true; } }
		TEMP.NUMBER = buren;
		return TEMP;
	}
public:          
	Chunk SET[32][32];


	int VOffset = 0;
	int IOffset = 0;
	//fills all the chunks with air and Sets the ChunksNeighbhors 
	void INIT()
	{
		for (int X = 0; X < 32; X++)
		{
			for (int Y = 0; Y < 32; Y++)
			{
				SET[X][Y].SetupChunk();
				SET[X][Y].ChunkX = X;
				SET[X][Y].ChunkY = Y;
			}
		}

		for (int X = 0; X < 32; X++) //loop through every chunk and assign their pointers its neighbors 
		{
			for (int Y = 0; Y < 32; Y++)
			{
				int CurrentChunkX = SET[X][Y].ChunkX;
				int CurrentChunkY = SET[X][Y].ChunkY;

				int FrontX = CurrentChunkX;
				int FrontY = CurrentChunkY + 1;
				int BackX = CurrentChunkX;
				int BackY = CurrentChunkY - 1;
				int RightX = CurrentChunkX + 1;
				int RightY = CurrentChunkY;
				int LeftX = CurrentChunkX - 1;
				int LeftY = CurrentChunkY;

				for (int FX = 0; FX < 32; FX++) //find the specified coordinates (needs to be optimized) FRONT
				{
					for (int FY = 0; FY < 32; FY++)
					{
						if (SET[FX][FY].ChunkX == FrontX && SET[FX][FY].ChunkY == FrontY) //front
						{
							SET[X][Y].FrontChunk = &SET[FX][FY];
							SET[X][Y].FrontChunkNeighbhor = true;
						}
						if (SET[FX][FY].ChunkX == BackX && SET[FX][FY].ChunkY == BackY) //back
						{
							SET[X][Y].BackChunk = &SET[FX][FY];
							SET[X][Y].BackChunkNeighbhor = true;
						}
						if (SET[FX][FY].ChunkX == RightX && SET[FX][FY].ChunkY == RightY) //right
						{
							SET[X][Y].RightChunk = &SET[FX][FY];
							SET[X][Y].RightChunkNeighbhor = true;
						}
						if (SET[FX][FY].ChunkX == LeftX && SET[FX][FY].ChunkY == LeftY) //left
						{
							SET[X][Y].LeftChunk = &SET[FX][FY];
							SET[X][Y].LeftChunkNeighbhor = true;
						}


					}
				}

			}
		}
	}


	//finds a chunk's Neighbhors. (X,Y gives the location of a chunk in the chunk array. not in the world)
	void FindChunkNeighbhors(int X, int Y)
	{
		int CurrentChunkX = SET[X][Y].ChunkX;
		int CurrentChunkY = SET[X][Y].ChunkY;

		int FrontX = CurrentChunkX;
		int FrontY = CurrentChunkY + 1;
		int BackX = CurrentChunkX;
		int BackY = CurrentChunkY - 1;
		int RightX = CurrentChunkX + 1;
		int RightY = CurrentChunkY;
		int LeftX = CurrentChunkX - 1;
		int LeftY = CurrentChunkY;


		SET[X][Y].FrontChunkNeighbhor = false;
		SET[X][Y].BackChunkNeighbhor = false;
		SET[X][Y].LeftChunkNeighbhor = false;
		SET[X][Y].RightChunkNeighbhor = false;


		for (int FX = 0; FX < 32; FX++) //find the specified coordinates (needs to be optimized) FRONT
		{
			for (int FY = 0; FY < 32; FY++)
			{
				if (SET[FX][FY].ChunkX == FrontX && SET[FX][FY].ChunkY == FrontY) //front
				{
					SET[X][Y].FrontChunk = &SET[FX][FY];
					SET[X][Y].FrontChunkNeighbhor = true;
				}
				if (SET[FX][FY].ChunkX == BackX && SET[FX][FY].ChunkY == BackY) //back
				{
					SET[X][Y].BackChunk = &SET[FX][FY];
					SET[X][Y].BackChunkNeighbhor = true;
				}
				if (SET[FX][FY].ChunkX == RightX && SET[FX][FY].ChunkY == RightY) //right
				{
					SET[X][Y].RightChunk = &SET[FX][FY];
					SET[X][Y].RightChunkNeighbhor = true;
				}
				if (SET[FX][FY].ChunkX == LeftX && SET[FX][FY].ChunkY == LeftY) //left
				{
					SET[X][Y].LeftChunk = &SET[FX][FY];
					SET[X][Y].LeftChunkNeighbhor = true;
				}


			}
		}




	}

	//gets the furthest away chunk for the specified positions. then returns the location of the chunk in the OutChunk variables
	void GetFurthestChunk(int CurX,int CurY,int &OutChunkX, int& OutChunkY)
	{
		int DistanceMax = 0;
		int FarChunkX;
		int FarChunkY;
		for (int X =0; X<32; X++) 
		{
			for (int Y = 0; Y < 32; Y++) 
			{
				int DIST = sqrt(pow((CurX - this->SET[X][Y].ChunkX), 2) + pow((CurY - this->SET[X][Y].ChunkY), 2));
				if (DIST > DistanceMax) { DistanceMax = DIST; FarChunkX = X; FarChunkY = Y; }
			
			
			
			}

		}
		OutChunkX = FarChunkX;
		OutChunkY = FarChunkY;
	}

	//checks if a spot isnt already occupied by another chunk
	bool IsChunkSpotavailable(int CX, int CY) 
	{
		
		for (int X = 0; X < 32; X++)
		{
			for (int Y = 0; Y < 32; Y++)
			{
				if (CX == this->SET[X][Y].ChunkX && CY == this->SET[X][Y].ChunkY) 
				{
					return false;
			
				}
			}

		}
	
		return true;
	}






	//moves a chunk's world position. and sets its ReGenFlag to True
	void MoveChunk(int TargetChunkX,int TargetChunkY,int NEWX,int NEWY) 
	{
		this->SET[TargetChunkX][TargetChunkY].ChunkX = NEWX;
		this->SET[TargetChunkX][TargetChunkY].ChunkY = NEWY;
		this->SET[TargetChunkX][TargetChunkY].ReGenFlag = true;
		//std::cout << "MOVED!";
	}
	
	
	
	
	
	
	
	
	//loops through each chunk in the set and generates each one
	void GenerateSet()
	{
		for (int X = 0; X < 32; X++)
		{
			for (int Y = 0; Y < 32; Y++)
			{
				GenerateWorld(SET[X][Y]);
			}
		}
	}
	
	//generates the mesh of a chunk. ChunkX and ChunkY ARE FOR SELECTING A CHUNK.NOT FOR WORLD GENERATION COORDS
	void GenerateMesh(GLuint(&indices)[300000], GLuint(&vertices)[1572864], int ChunkX, int ChunkY)
	{
		VOffset = 0;
		IOffset = 0;

		for (int X = 0; X < 15; X++)
		{
			for (int Z = 0; Z < 15; Z++)
			{
				for (int Y = 0; Y < 254; Y++)
				{
					if (this->SET[ChunkX][ChunkY].ChunkData[X][Y][Z] != 0)
					{
						this->SET[ChunkX][ChunkY];
						SIDES T = checkburen(X, Y, Z, this->SET[ChunkX][ChunkY]);
						if (T.NUMBER < 6)
						{

							AddCube(X, Y, Z, T, this->SET[ChunkX][ChunkY].ChunkData[X][Y][Z], indices, vertices);
						}
					}

				}
			}
		}
		this->SET[ChunkX][ChunkY].ReMeshFlag = false;

	}
	
};