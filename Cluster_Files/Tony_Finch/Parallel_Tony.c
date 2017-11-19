/*---------------------------------------------
Parallel implementation of Tony Finch Approach
Author:  201501452 - Dhruv Patel
	 201501408 - Raj Jakasaniya

Detail comment is in serial implementation here we have provided comment for parallel part only
---------------------------------------------*/


#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>

int **curr;
int **next;
int **tem;
int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

void print(int row,int col)
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

int neighbours(int x,int y,int row,int col){
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

void update(int row,int col)
{
    int i,j;
    #pragma omp parallel for private(i,j)			/* parallelizing the outer for loop (row wise )  */
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
void update_neighbours(int x,int y,int row,int col,int status)
{
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
void change(int row,int col){
    int x,y;
    #pragma omp parallel for private(x,y)			/* parallelizing the outer for loop (row wise )  */
    for(x=0;x<row;x++)
    {
        for(y=0;y<col;y++)
        {
            int alive = tem[x][y];
            int state = curr[x][y];
            if(state==1 && (alive>3 || alive<2))
            {
                update_neighbours(x,y,row,col,-1);
                curr[x][y]=0;
            }
            else if(state==0 && alive==3)
            {
                update_neighbours(x,y,row,col,1);
                curr[x][y]=1;
            }
            
        }
    }

    #pragma omp parallel for private(y)				/* parallelizing the outer for loop (row wise )  */
    for(x=0;x<row;x++)
    {
        for(y=0;y<col;y++)
        {
            tem[x][y]=next[x][y];
        }
    }
}

int main(int argc , char** argv)				/* taking arguments for matrix size, no. of steps and no. of threads  */
{

    int i,j,row,col,t_steps,steps;
    double start,stop;
    float x;

    row=atoi(argv[1]);						/* initialising the no. of rows, column, no. of steps from arguments and no. of threads */
    col=atoi(argv[2]);
    t_steps=atoi(argv[3]);
    omp_set_num_threads(atoi(argv[4]));

    curr=(int **)(malloc(row*sizeof(int *)));
    next=(int **)(malloc(row*sizeof(int *)));
    tem=(int **)(malloc(row*sizeof(int *)));
    for(i=0;i<row;i++){
        curr[i]=(int *)(malloc(col*sizeof(int)));
        next[i]=(int *)(malloc(col*sizeof(int)));
        tem[i]=(int *)(malloc(col*sizeof(int)));
        for(j=0;j<col;j++){
            x = rand()/((float)RAND_MAX + 1);
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
    
    char file_name[100];

    strcpy(file_name,"Parallel_Tony_cores_");			/* opening and writing in file  */
    strcat(file_name,argv[4]);
    strcat(file_name,".txt");
    FILE *fp = fopen(file_name,"a+");

    fprintf(fp,"%0.10lf\n", (stop-start));
}
