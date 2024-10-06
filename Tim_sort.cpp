#include <iostream>
using namespace std;

const int RUN = 32; // Size of the run

// Utility function to find the minimum of two integers
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Insertion sort for sorting a small section of the array
void insertionSort(int a[], int beg, int end) {
    for (int i = beg + 1; i <= end; i++) {
        int temp = a[i];
        int j = i - 1;

        while (j >= beg && temp < a[j]) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = temp;
    }
}

// Merge two sorted subarrays
void merge(int a[], int beg, int mid, int end) {
    int n1 = mid - beg + 1;
    int n2 = end - mid;

    // Temporary arrays to hold the split parts
    int* LeftArray = new int[n1];
    int* RightArray = new int[n2];

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        LeftArray[i] = a[beg + i];
    for (int j = 0; j < n2; j++)
        RightArray[j] = a[mid + 1 + j];

    int i = 0, j = 0, k = beg;
    
    // Merge the temporary arrays back into the original array
    while (i < n1 && j < n2) {
        if (LeftArray[i] <= RightArray[j]) {
            a[k++] = LeftArray[i++];
        } else {
            a[k++] = RightArray[j++];
        }
    }

    // Copy remaining elements, if any
    while (i < n1) {
        a[k++] = LeftArray[i++];
    }
    while (j < n2) {
        a[k++] = RightArray[j++];
    }

    // Clean up
    delete[] LeftArray;
    delete[] RightArray;
}

// Timsort implementation
void timSort(int a[], int n) {
    // Sort individual subarrays of size RUN
    for (int i = 0; i < n; i += RUN) {
        insertionSort(a, i, min(i + RUN - 1, n - 1));
    }

    // Start merging from size RUN (or 32)
    for (int size = RUN; size < n; size *= 2) {
        for (int beg = 0; beg < n; beg += 2 * size) {
            int mid = beg + size - 1;
            int end = min(beg + 2 * size - 1, n - 1);

            // Merge subarrays a[beg...mid] and a[mid+1...end]
            if (mid < end) {
                merge(a, beg, mid, end);
            }
        }
    }
}

// Function to print the array elements
void printArr(int a[], int n) {
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

// Main function
int main() {
    int a[] = { 39, 11, 30, 26, 24, 7, 0, 31, 16 };
    int n = sizeof(a) / sizeof(a[0]);

    cout << "Before sorting array elements are:\n";
    printArr(a, n);

    timSort(a, n);

    cout << "After sorting array elements are:\n";
    printArr(a, n);

    return 0;
}
