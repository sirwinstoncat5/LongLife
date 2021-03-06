//Life library: contains basic life/stabilife tools

#include <stdlib.h>

void drawFrame(void);
int liveNeighbors(int x, int y, int gridSize); //Uses global temp grid

int **tempGrid;

long int simStableLife(int gridSize, int setMemory[], int setNum, int chunkSize)
{
	int i, j;
	
	tempGrid=malloc(gridSize*sizeof(int*));
	//There should be null-pointer checking here, but I'll let the program crash instead-I don't feel like writing tons of for loops right now.
	for(i=0; i<gridSize; i++)
	{
		tempGrid[i]=malloc(gridSize*sizeof(int));
		//More error checking, again, skipped for the time being.
	}
	
	for(i=0; i<gridSize; i++) for(j=0; j<gridSize; j++) tempGrid[i][j]=setMemory[chunkSize*chunkSize*4*setNum+chunkSize*2*i+j]; //Copy grid into buffer (setMemory weird addressing copied from main.c)
	
	int action=0;
	int gen=1;
	
	for(;;) //Mainloop
	{
		//drawFrame();
		if(action>0) action=0;
		for(i=0; i<gridSize; i++) for(j=0; j<gridSize; j++)
		{	
			switch(liveNeighbors(i, j, gridSize))
			{
				case 0:
				case 1:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
					if(tempGrid[i][j]==1)
					{
						tempGrid[i][j]=0;
						action++;
					}
					break;
				case 3:
					if(tempGrid[i][j]==0)
					{
						tempGrid[i][j]=1;
						action++;
					}
					break;
			}
		}
		
		gen++;
		
		if(gen>=999999) return 999999;
		//Since 999999 generations have passed and there is no stable pattern,
		//we cap the simulation at 999999 generations to save CPU time and prevent
		//patterns like a Gosper glider gun from hanging the simulation.
		
		
		if (action==0) return gen;
	}
}

int liveNeighbors(int x, int y, int gridSize)
{
	int count=0;
	int a, b;
	
	a=x-1;
	b=y-1;
	if(a<0 || b<0 || a> gridSize|| b>gridSize) ;
	else if(tempGrid[a][b]==1) count++;
	
	a=x;
	b=y-1;
	if(a<0 || b<0 || a>gridSize || b>gridSize) ;
	else if(tempGrid[a][b]==1) count++;
	
	a=x+1;
	b=y-1;
	if(a<0 || b<0 || a>gridSize || b>gridSize) ;
	else if(tempGrid[a][b]==1) count++;
	
	a=x-1;
	b=y;
	if(a<0 || b<0 || a>gridSize || b>gridSize) ;
	else if(tempGrid[a][b]==1) count++;
	
	a=x+1;
	b=y;
	if(a<0 || b<0 || a>gridSize || b>gridSize) ;
	else if(tempGrid[a][b]==1) count++;
	
	a=x-1;
	b=y+1;
	if(a<0 || b<0 || a>gridSize || b>gridSize) ;
	else if(tempGrid[a][b]==1) count++;
	
	a=x;
	b=y+1;
	if(a<0 || b<0 || a>gridSize || b>gridSize) ;
	else if(tempGrid[a][b]==1) count++;
	
	a=x+1;
	b=y+1;
	if(a<0 || b<0 || a>gridSize || b>gridSize) ;
	else if(tempGrid[a][b]==1) count++;
	
	return count;
}
/*void drawFrame(void) //Never called, here for reference
{
	system("cls");
	int i, j;
	for(i=0; i<GRIDSIZE; i++) 
	{
		for(j=0; j<GRIDSIZE; j++)
		{
			if(grid[i][j]==1) printf("*");
			else printf(" ");
		}
		printf("\n");
	}
	printf("\nBirths: %d\nDeaths: %d\nGeneration: %d", births, deaths, gen);
}*/

