#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME 50

struct Product {
    int id;
    float price;
    char name[MAX_NAME];
};

// Function prototypes
void quickSort(struct Product arr[], int low, int high);
int partition(struct Product arr[], int low, int high);
void mergeSort(struct Product arr[], int left, int right);
void merge(struct Product arr[], int left, int mid, int right);
void printArray(struct Product arr[], int size);

// Quick Sort Implementation
void quickSort(struct Product arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(struct Product arr[], int low, int high) {
    struct Product pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].price <= pivot.price) {
            i++;
            struct Product temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    struct Product temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// Merge Sort Implementation
void mergeSort(struct Product arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void merge(struct Product arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    struct Product *L = (struct Product *)malloc(n1 * sizeof(struct Product));
    struct Product *R = (struct Product *)malloc(n2 * sizeof(struct Product));

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i].id <= R[j].id) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void printArray(struct Product arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("ID: %d, Price: %.2f, Name: %s\n", arr[i].id, arr[i].price, arr[i].name);
    }
    printf("\n");
}

int main() {
    struct Product products[] = {
        {1, 29.99, "Product A"},
        {3, 15.50, "Product B"},
        {2, 45.75, "Product C"},
        {5, 9.99, "Product D"},
        {4, 32.50, "Product E"}
    };
    int n = sizeof(products) / sizeof(products[0]);

    printf("Original Array:\n");
    printArray(products, n);

    // Quick Sort (sorting by price)
    quickSort(products, 0, n - 1);
    printf("After Quick Sort (by price):\n");
    printArray(products, n);

    // Merge Sort (sorting by ID)
    mergeSort(products, 0, n - 1);
    printf("After Merge Sort (by ID):\n");
    printArray(products, n);

    return 0;
}