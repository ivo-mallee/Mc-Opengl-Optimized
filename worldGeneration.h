#pragma once
#include "Chunk.h"
#include <noise/noise.h>

noise::module::Perlin myModule;



//inits the World Generator's noise function.
void initGeneration() 
{
	myModule.SetSeed(22);
	myModule.SetFrequency(2.0);
	myModule.SetLacunarity(2.375);
	myModule.SetOctaveCount(8);
	myModule.SetPersistence(0.5);
	myModule.SetNoiseQuality(noise::QUALITY_STD);
}

//take an X,Y value and a Chunk Object and sets the height based on a noise map
void NormalGeneration(int X,int Z, Chunk &TargetChunk)
{

	
	int Scale = 200; //the higher the less pointy the terrain is
	int multiplier = 100;
	double T = abs(myModule.GetValue((double)(X + (TargetChunk.ChunkX * 15)) / Scale, (double)(Z + (TargetChunk.ChunkY * 15)) / Scale, 255));
	int i = T * multiplier;
	if (i > 150) { i = 150; std::cout << "BUILD LIMIT REACHED"; }
	TargetChunk.ChunkData[X][i + 100][Z] = 3; //top layer grass
	TargetChunk.ChunkData[X][i + 99][Z] = 1; //dirt
	TargetChunk.ChunkData[X][i + 98][Z] = 1; //dirt
	TargetChunk.ChunkData[X][i + 97][Z] = 1; //dirt
	for (int P = i + 96; P > -1; P--)
	{
		TargetChunk.ChunkData[X][P][Z] = 2; //stone
	}




}

//creates a simple Wave pattern usefull for debugging chunks
void SinGeneration(int X, int Z, Chunk& TargetChunk)
{
	
	
	
	float T = sin( (double) (Z + (TargetChunk.ChunkY * 15) )/20 );

	int VALUE = T * 100;
	if (VALUE > 100) { VALUE = 100; }

	TargetChunk.ChunkData[X][100+ VALUE][Z] = 5; //stone
	
	
	for (int i = 100+VALUE; i>0; i--) 
	{
		TargetChunk.ChunkData[X][i][Z] = 5; //stone
	}
	

}







//empties the provided chunk and generates the terrain
void GenerateWorld(Chunk &TargetChunk) {


	
	for (int X = 0; X < 15; X++)
	{
		for (int Z = 0; Z < 15; Z++)
		{
			for (int Y = 1; Y < 255; Y++)
			{
				TargetChunk.ChunkData[X][Y][Z] = 0;
			}
			
			NormalGeneration(X,Z,TargetChunk);
			//SinGeneration(X, Z, TargetChunk);





		}
	}
	
	TargetChunk.ReGenFlag = false; //we have done the generation. this chunk no longer needs to be regenerated
	TargetChunk.ReMeshFlag = true; //the chunk's data has changed. its in need of remeshing
}