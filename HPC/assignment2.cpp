#include<iostream>
#include<omp.h>
#include<bits/stdc++.h>

using namespace std;

void sequential_bubble_sort(int arr[],int n){
    int temp[n];
    for(int i = 0 ; i < n; i++){
        temp[i] = arr[i];
    }

  
    for(int i = 0; i < n - 1; i ++){
        for(int j = 0; j < n - i - 1; j++){
            if(temp[j] > temp[j+1]){
                swap(temp[j],temp[j+1]);
            }
        }
    }
    
    cout << "Sequential Bubble  Sort: "<<endl;;
    for(int i = 0 ; i < n; i++){
        cout << temp[i] << " ";
    }
    cout << endl;
    

}

void parallel_bubble_sort(int arr[],int n){
    int temp[n];
    for(int i = 0 ; i < n; i++){
        temp[i] = arr[i];
    }
    
    for(int k = 0; k < n;k ++){
        if(k % 2 == 0){
            #pragma omp parallel for
                for(int i = 1; i < n - 1; i += 2){
                    if(temp[i] > temp[i+1]){
                        swap(temp[i],temp[i+1]);
                    }
                }
        }
        else{
            #pragma omp parallel for
                for(int i = 0; i < n - 1; i += 2){
                    if(temp[i] > temp[i+1]){
                        swap(temp[i],temp[i+1]);
                    }
                }
        }
    }
    
    cout << "Parallel Bubble  Sort: "<<endl;;
    for(int i = 0 ; i < n; i++){
        cout << temp[i] << " ";
    }
    cout << endl;
    
}

void merge(int array[],int low, int mid, int high,int n){
    int temp[n];
    int i = low;
    int j = mid + 1;
    int k = 0;
    while((i <= mid) && (j <= high)){
        if(array[i] >= array[j]){
            temp[k] = array[j];
            k++;
            j++;
        }
        else{
            temp[k] = array[i];
            k++;
            i++;
        }
    }
    while(i <= mid){
        temp[k] = array[i];
        k++;
        i++;
    }
    while(j <= high){
        temp[k] = array[j];
        k++;
        j++;
    }

    k = 0;
    for(int i = low;i <= high;i++){
        array[i] = temp[k];
        k++;
    }
}

void mergesort(int arr[],int low,int high,int n){
    if(low < high){
        int mid = (low + high) / 2;
        mergesort(arr,low,mid,n);
        mergesort(arr,mid+1,high,n);
        merge(arr,low,mid,high,n);
    }
}

void perform_merge_sort(int arr[],int n){
    int temp[n];
    for(int i = 0 ; i < n; i++){
        temp[i] = arr[i];
    }
    
    mergesort(temp,0,n-1,n);
   
    cout << "Merge  Sort: "<<endl;;
    for(int i = 0 ; i < n; i++){
        cout << temp[i] << " ";
    }
    cout << endl;
    
}

void p_mergesort(int array[],int low,int high,int n){
    if(low < high){
        int mid = (low + high) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
                p_mergesort(array,low,mid,n);
            #pragma omp section
                p_mergesort(array,mid+1,high,n);
        }
        merge(array,low,mid,high,n);
    }
}

void perform_p_merge_sort(int arr[],int n){
    int array[n];
    for(int i = 0 ; i < n; i++){
        array[i] = arr[i];
    }
   
    p_mergesort(array,0,n-1,n);
   
    cout << "Parallel Merge  Sort: "<<endl;;
    for(int i = 0 ; i < n; i++){
        cout << array[i] << " ";
    }
    cout << endl;
    
}



int main(int argc, char const *argv[])
{
    // int n;
    // int MAX = 1000;
    int n;
    cout << "Enter n of array: ";
    cin >> n;
    int arr[n];
    int temp;
    for(int i = 0 ; i < n; i ++){
        cout<<"Enter element: ";
        cin>>temp;
        arr[i]=temp;
    }
    cout << endl;
    sequential_bubble_sort(arr,n);
    parallel_bubble_sort(arr,n);
    perform_merge_sort(arr,n);
    perform_p_merge_sort(arr,n);

    return 0;
}
