#ifndef MYSORT_H
#define MYSORT_H

template<typename T, typename Compare>
void quickSort(T arr[], int left, int right, Compare cmp) {
    if (left >= right) {
        return;
    }
    int i = left, j = right;
    T pivot = arr[(left + right) / 2];
    while (i <= j) {
        while (cmp(arr[i], pivot)) {
            i++;
        }
        while (cmp(pivot, arr[j])) {
            j--;
        }
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    quickSort(arr, left, j, cmp);
    quickSort(arr, i, right, cmp);
}

#endif // MYSORT_H


