#include <iostream>
#include <omp.h>
#include <bits/stdc++.h>

using namespace std;

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void bubble_sort(int arr[], int n)
{
    int temp[n];
    for (int i = 0; i < n; i++)
    {
        temp[i] = arr[i];
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (temp[j] > temp[j + 1])
            {
                swap(temp[j], temp[j + 1]);
            }
        }
    }
    cout << "Bubble Sort: " << endl;
    printArray(temp, n);
}

void parallel_bubble_sort(int arr[], int n)
{
    int temp[n];
    for (int i = 0; i < n; i++)
    {
        temp[i] = arr[i];
    }

    for (int k = 0; k < n; k++)
    {
        if (k % 2 == 0)
        {
#pragma omp parallel for
            for (int i = 1; i < n - 1; i += 2)
            {
                if (temp[i] > temp[i + 1])
                {
                    swap(temp[i], temp[i + 1]);
                }
            }
        }
        else
        {
#pragma omp parallel for
            for (int i = 0; i < n - 1; i += 2)
            {
                if (temp[i] > temp[i + 1])
                {
                    swap(temp[i], temp[i + 1]);
                }
            }
        }
    }

    cout << "Parallel Bubble Sort: " << endl;
    printArray(temp, n);
}

void merge(int arr[], int low, int mid, int high, int n)
{
    int temp[n];
    int i = low;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= high)
    {
        if (arr[i] >= arr[j])
        {
            temp[k] = arr[j];
            j++;
            k++;
        }
        else
        {
            temp[k] = arr[i];
            i++;
            k++;
        }
    }

    while (i <= mid)
    {
        temp[k] = arr[i];
        k++;
        i++;
    }

    while (j <= high)
    {
        temp[k] = arr[j];
        j++;
        k++;
    }

    k = 0;
    for (int i = low; i <= high; i++)
    {
        arr[i] = temp[k];
        k++;
    }
}

void merge_sort(int arr[], int low, int high, int n)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        merge_sort(arr, low, mid, n);
        merge_sort(arr, mid + 1, high, n);
        merge(arr, low, mid, high, n);
    }
}

void parallel_merge_sort(int arr[], int low, int high, int n)
{
    if (low < high)
    {
        int mid = (low + high) / 2;

#pragma omp parallel sections
        {
#pragma omp section
            merge_sort(arr, low, mid, n);
#pragma omp section
            merge_sort(arr, mid + 1, high, n);
        }
        merge(arr, low, mid, high, n);
    }
}

void perform_merge_sort(int arr[], int n)
{
    int temp[n];
    for (int i = 0; i < n; i++)
    {
        temp[i] = arr[i];
    }

    merge_sort(temp, 0, n - 1, n);

    cout << "Merge Sort: " << endl;
    printArray(temp, n);
}

void perform_parallel_merge_sort(int arr[], int n)
{
    int temp[n];
    for (int i = 0; i < n; i++)
    {
        temp[i] = arr[i];
    }

    parallel_merge_sort(temp, 0, n - 1, n);

    cout << "Parallel Merge Sort: " << endl;
    printArray(temp, n);
}

int main()
{
    int n;
    cout << "Enter size: ";
    cin >> n;

    int arr[n];
    int temp;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter element: ";
        cin >> temp;
        arr[i] = temp;
    }

    bubble_sort(arr, n);
    parallel_bubble_sort(arr, n);
    perform_merge_sort(arr, n);
    perform_parallel_merge_sort(arr, n);
}