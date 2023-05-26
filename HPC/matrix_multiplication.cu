%%cu
#include<stdio.h>
#include<cuda.h>


__global__ void matproduct(int *l,int *m, int *n)
{
    int x=blockIdx.x;
    int y=blockIdx.y;
    int k;
  
n[2*y+x]=0;
for(k=0;k<2;k++)
   {
    n[2*y+x]=n[2*y+x]+l[2*y+k]*m[2*k+x];
   }
}

int main()
{
    int row1=2, col1=2, row2=2, col2=2;
    int a[row1][col1];
    int b[row2][col2];
    int c[row1][col2];
    int *d,*e,*f;
    int i,j;

    //printf("\n Enter elements of first matrix of size 2*3\n");
    for(i=0;i<2;i++)
    {
        for(j=0;j<2;j++)
            {
                a[i][j]=i+j;
            }
    }
 for(i=0;i<2;i++)
    {
        for(j=0;j<2;j++)
        {
              printf("%d\t",a[i][j]);
        }
        printf("\n");
    }
    //printf("\n Enter elements of second matrix of size 3*2\n");
        for(i=0;i<2;i++)
        {
            for(j=0;j<2;j++)
                {
                    b[i][j]=i+j;
                }
        }
 for(i=0;i<2;i++)
    {
        for(j=0;j<2;j++)
        {
              printf("%d\t",b[i][j]);
        }
        printf("\n");
    }

    cudaMalloc((void **)&d,row1*col1*sizeof(int));
    cudaMalloc((void **)&e,row2*col2*sizeof(int));
    cudaMalloc((void **)&f,row1*col2*sizeof(int));

 cudaMemcpy(d,a,row1*col1*sizeof(int),cudaMemcpyHostToDevice);
 cudaMemcpy(e,b,row2*col2*sizeof(int),cudaMemcpyHostToDevice);

dim3 grid(col2,row1);
/* Here we are defining two dimensional Grid(collection of blocks) structure. Syntax is dim3 grid(no. of columns,no. of rows) */

    matproduct<<<grid,1>>>(d,e,f);

 cudaMemcpy(c,f,row1*col2*sizeof(int),cudaMemcpyDeviceToHost);
    printf("\nProduct of two matrices:\n ");
    for(i=0;i<2;i++)
    {
        for(j=0;j<2;j++)
        {
              printf("%d\t",c[i][j]);
        }
        printf("\n");
    }

    cudaFree(d);
    cudaFree(e);
    cudaFree(f);

    return 0;
}