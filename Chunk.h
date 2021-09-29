#pragma once
#include "Blocks.h"
class Chunk {       
public:             
		int ChunkX = 0; //ChunkX for world generation
		int ChunkY = 0; //ChunkY for world generation
		int ChunkData[15][255][15]; //data to store blockdata



		bool LeftChunkNeighbhor = false;
		bool RightChunkNeighbhor = false;
		bool FrontChunkNeighbhor = false;
		bool BackChunkNeighbhor = false;





		bool ReGenFlag = true; //flag that signiefies tha the chunk is in need of being regenerated (world generation)
		bool ReMeshFlag = true; //flag that signifies that the chunk is in need of remeshing

		
		Chunk* LeftChunk; //pointers to its neighbors to prevent drawing of triangles intersecting between chunks (used in the chunk set)
		Chunk* RightChunk;
		Chunk* BackChunk;
		Chunk* FrontChunk;

		




		void SetupChunk()
		{
			LeftChunkNeighbhor = false;
			RightChunkNeighbhor = false;
			FrontChunkNeighbhor = false;
			BackChunkNeighbhor = false;
			
			
			
			
			
			for (int X = 0; X < 15; X++) //fill entire array with zero
			{
				for (int Z = 0; Z < 15; Z++)
				{
					for (int Y = 0; Y < 255; Y++)
					{
						this->ChunkData[X][Y][Z] = 0;

					}


				}
			}

			
			for (int X = 0; X < 15; X++)
			{
				for (int Z = 0; Z < 15; Z++)
				{
					for (int Y = 0; Y < 1; Y++)
					{
						this->ChunkData[X][Y][Z] = 1;

					}


				}
			}
			
		}

};