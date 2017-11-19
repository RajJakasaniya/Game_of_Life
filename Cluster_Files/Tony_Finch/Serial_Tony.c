/*---------------------------------------------
Serial implementation of Tony Finch Approach
Author:  201501452 - Dhruv Patel
	 201501408 - Raj Jakasaniya
---------------------------------------------*/

#include <stdio.h>						/* including the header */
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int **curr;							/* making gobal 2D array */
int **next;
int **tem;
int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};				/* for traversing neighbours  */
int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

void print(int row,int col)					/* function for printing output martix which take no. of row and no. of column as parameter */
{
	int i, j;
	for (i = 0; i < row; ++i)
	{
		for (j = 0; j < col; ++j)
		{
			printf("%d ",curr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int neighbours(int x,int y,int row,int col){			/* this function gives the no. of neighbours alive cell (x,y)  */
    int count=0,temp=0;
    for(temp=0;temp<8;temp++){
        int i=x+dx[temp];
        int j=y+dy[temp];
        
        if(i<0) i=i+row;
        if(j<0) j=j+col;

        if(i>=row) i=i-row;
        if(j>=col) j=j-col;

        count=count+curr[i][j];      
    }
    return count;
}

void update(int row,int col)				/* making matrix of no. of neighbours alive  */
{
    int i,j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            int live = neighbours(i,j,row,col);
            tem[i][j]=live;
            next[i][j]=live;
        }
    }
}
void update_neighbours(int x,int y,int row,int col,int status)		/*  this will update the no. of neighbour to cell (x,y) if the state of cell (x,y) changes  */
{									/* here status will indicate the change if dead then -1 and if alive then +1  */
    int temp=0;
    for(temp=0;temp<8;temp++){
        int i=x+dx[temp];
        int j=y+dy[temp];
        
        if(i<0) i=i+row;
        if(j<0) j=j+col;

        if(i>=row) i=i-row;
        if(j>=col) j=j-col;

        next[i][j]=next[i][j] + status;
    }
}
void change(int row,int col){			/*  this function change the state of cell according to the rules */
    int x,y;
    for(x=0;x<row;x++)
    {
        for(y=0;y<col;y++)
        {
            int alive = tem[x][y];
            int state = curr[x][y];
            if(state==1 && (alive>3 || alive<2))		/*  if the cell is live and it is underpopulated or overpopulated then it dies  */
            {
                update_neighbours(x,y,row,col,-1);
                curr[x][y]=0;
            }
            else if(state==0 && alive==3)			/*  if cell is dead and the no. of neighbours alive is 3 then cell becomes alive */
            {
                update_neighbours(x,y,row,col,1);
                curr[x][y]=1;
            }
            
        }
    }
    for(x=0;x<row;x++)
    {
        for(y=0;y<col;y++)
        {
            tem[x][y]=next[x][y];			/* coping new no. of neighbours matrix to tem matrix  */
        }
    }
}

int main(int argc , char** argv)			/* taking arguments for matrix size and no. of steps  */
{

    int i,j,row,col,t_steps,steps;
    double start,stop;
    float x;

    row=atoi(argv[1]);					/* initialising the no. of rows, column, and no. of steps from arguments */
    col=atoi(argv[2]);
    t_steps=atoi(argv[3]);

    curr=(int **)(malloc(row*sizeof(int *)));		/* allocatting the memory of row using malloc  */
    next=(int **)(malloc(row*sizeof(int *)));
    tem=(int **)(malloc(row*sizeof(int *)));
    for(i=0;i<row;i++){
        curr[i]=(int *)(malloc(col*sizeof(int)));		/* allocatting the memory of column using malloc  */
        next[i]=(int *)(malloc(col*sizeof(int)));
        tem[i]=(int *)(malloc(col*sizeof(int)));
        for(j=0;j<col;j++){
            x = rand()/((float)RAND_MAX + 1);			/*  generating the random input  */
            if(x<0.5){
	            curr[i][j] = 0;
            }else{
	            curr[i][j] = 1;
            }    
        }
    }

    start = omp_get_wtime();
    
    update(row,col);

    for(steps=0;steps<t_steps;steps++){
        change(row,col);
    }    

    //print(row,col);    
    
    stop = omp_get_wtime();
    
    char filename[100];

    strcpy(filename,"Serial_Tony.txt");
    FILE *fp = fopen(filename,"a+");			/* opening a file  */

    fprintf(fp,"%0.10lf\n", (stop-start));		/* writing time in file */	
}
