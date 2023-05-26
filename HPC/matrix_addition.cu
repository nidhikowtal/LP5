#include<stdio.h>
#include<cuda.h>
__global__ void matadd(int *l,int *m, int *n)
{
    int x=blockIdx.x; //By using blockIdx.x, we can determine the position of the current block along the x-axis of the grid.
    int y=blockIdx.y;
    int id=gridDim.x * y +x; // Since the grid can have multiple dimensions (in this case, it's a 2D grid), we need to calculate a unique identifier for each thread that takes into account both the x and y coordinates
    n[id]=l[id]+m[id];
}
int main()
{
    int a[2][3];
    int b[2][3];
    int c[2][3];
    int *d,*e,*f;
    int i,j;
    
    for(i=0;i<2;i++)
    {
        for(j=0;j<3;j++)
            {
                a[i][j]=i+j;
            }
    }
    
        for(i=0;i<2;i++)
        {
            for(j=0;j<3;j++)
                {
                    b[i][j]=i+j;
                }
        }
     // (void **)&d is used to pass the address of the pointer d to cudaMalloc. 
     // sizeof(int) gives the size of an integer in bytes. Multiplying it by 2 * 3 gives the total number of bytes required to store the matrix.
 
    cudaMalloc((void **)&d,2*3*sizeof(int));  // responsible for allocating device memory on the GPU.
    cudaMalloc((void **)&e,2*3*sizeof(int));
    cudaMalloc((void **)&f,2*3*sizeof(int));
 
    // When you allocate device memory using cudaMalloc, you are requesting a block of memory on the GPU with a specified size. 
    //This memory is used to store data that will be processed by the GPU kernels.
    
 cudaMemcpy(d,a,2*3*sizeof(int),cudaMemcpyHostToDevice);
 cudaMemcpy(e,b,2*3*sizeof(int),cudaMemcpyHostToDevice);
    
dim3 grid(3,2);
/* Here we are defining two dimensional Grid(collection of blocks) structure. Syntax is dim3 grid(no. of columns,no. of rows) */

    matadd<<<grid,1>>>(d,e,f);

 cudaMemcpy(c,f,2*3*sizeof(int),cudaMemcpyDeviceToHost);
    printf("\nSum of two matrices:\n ");
    for(i=0;i<2;i++)
    {
        for(j=0;j<3;j++)
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
