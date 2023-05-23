#include <iostream>
#include <omp.h>
#include <bits/stdc++.h>

using namespace std;

void serial_operations(vector<int> &arr, int n)
{
    int min_val_serial = arr[0];
    int max_val_serial = arr[0];
    int sum_serial = 0;

    auto start_serial = chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++)
    {
        min_val_serial = min(min_val_serial, arr[i]);
        max_val_serial = max(max_val_serial, arr[i]);
        sum_serial += arr[i];
    }

    double average_serial = (double)sum_serial / n;

    auto end_serial = chrono::high_resolution_clock::now();
    auto duration_serial = chrono::duration_cast<chrono::microseconds>(end_serial - start_serial);

    cout << "Serial Results:" << endl;
    cout << "Minimum value: " << min_val_serial << endl;
    cout << "Maximum value: " << max_val_serial << endl;
    cout << "Sum: " << sum_serial << endl;
    cout << "Average: " << average_serial << endl;
    cout << "Serial Execution Time: " << duration_serial.count() << " microseconds" << endl;
}

void parallel_operations(vector<int> &arr, int n)
{
    int min_val_parallel = arr[0];
    int max_val_parallel = arr[0];
    int sum_parallel = 0;

    auto start_parallel = chrono::high_resolution_clock::now();

#pragma omp parallel for reduction(min : min_val_parallel) reduction(max : max_val_parallel) reduction(+ : sum_parallel)
    for (int i = 0; i < n; i++)
    {
        min_val_parallel = min(min_val_parallel, arr[i]);
        max_val_parallel = max(max_val_parallel, arr[i]);
        sum_parallel += arr[i];
    }

    double average_parallel = (double)sum_parallel / n;

    auto end_parallel = chrono::high_resolution_clock::now();
    auto duration_parallel = chrono::duration_cast<chrono::microseconds>(end_parallel - start_parallel);

    cout << "\nParallel Results:" << endl;
    cout << "Minimum value: " << min_val_parallel << endl;
    cout << "Maximum value: " << max_val_parallel << endl;
    cout << "Sum: " << sum_parallel << endl;
    cout << "Average: " << average_parallel << endl;
    cout << "Parallel Execution Time: " << duration_parallel.count() << " microseconds" << endl;
}
int main()
{
    vector<int> arr = {10, 5, 7, 15, 3, 9, 12, 8};

    int n = arr.size();

    serial_operations(arr, n);
    parallel_operations(arr, n);

    return 0;
}
