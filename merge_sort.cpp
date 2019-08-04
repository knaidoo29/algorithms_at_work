#include <iostream>
#include <time.h>
//#include <cmath>

using namespace std;

// Functions Declarations --------------------------------------------------- //

// utility functions
void create_randoms(float randoms[], int size);
void get_index(int index[], int size);
void print_array(float array[], int size, bool);
void print_array(int array[], int size, bool);

// merge sort functions
int _get_split_count(int run);
void _sort_pair(float array_pair[2], int array_pair_index[2]);
void _merge(float arr1[], int arr1_in[], int size1, float arr2[], int arr_in2[], int size2, float merged_arr[],
        int merged_ind[]);
void merge_sort(float array[], int array_index[], int size);

// MAIN CODES --------------------------------------------------------------- //

int main(){

    int size;

    size = 20;

    cout << "\n Size of array : " << size << endl;

    float a[size];
    int a_i[size];

    cout << "\n Generating randoms..." << endl;

    create_randoms(a, size);
    get_index(a_i, size);

    cout << "\n Printing..." << endl;

    print_array(a, size, true);

    cout << "\n Merge sort..." << endl;

    merge_sort(a, a_i, size);

    cout << "\n Printing sorted randoms..." << endl;

    print_array(a, size, true);

    return 0;
}

// Functions ---------------------------------------------------------------- //

void create_randoms(float randoms[], int size){

    // Change initial random seed, which is based on the time.
    srand( (unsigned)time( NULL ) );

    // Assign random floats between 0 and 1 to the x and y arrays.
    for (int i = 0; i < size; i++)
    {
        randoms[i] = (float) rand()/RAND_MAX;
    }
}

void get_index(int index[], int size){

    // get index.
    for (int i = 0; i < size; i++)
    {
        index[i] = i;
    }
}

void print_array(float array[], int size, bool list){

    // Prints the float array.
    cout << "\n";
    for (int i = 0; i < size; i++)
    {
        if(list == true) {
            // Prints as a list.
            if(i < size-1) {
                cout << array[i] << ", ";
            }
            else{
                cout << array[i] << endl;
            }
        }
        else{
            // Prints each element on each line.
            cout << array[i] << endl;
        }
    }
}

void print_array(int array[], int size, bool list){

    // Prints the float array.
    cout << "\n";
    for (int i = 0; i < size; i++)
    {
        if(list == true) {
            // Prints as a list.
            if(i < size-1) {
                cout << array[i] << ", ";
            }
            else{
                cout << array[i] << endl;
            }
        }
        else{
            // Prints each element on each line.
            cout << array[i] << endl;
        }
    }
}

int _get_split_count(int run){

    int splits_i, split_count;

    splits_i = 1;
    split_count = 1;
    while(splits_i < run){
        split_count *= 2;
        splits_i += 1;
    }

    return split_count;
}

void _sort_pair(float array_pair[2], int array_pair_index[2]){

    float x1, x2;
    int ind1, ind2;

    x1 = array_pair[0];
    x2 = array_pair[1];
    ind1 = array_pair_index[0];
    ind2 = array_pair_index[1];
    if(x2 < x1) {
        array_pair[0] = x2;
        array_pair[1] = x1;
        array_pair_index[0] = ind2;
        array_pair_index[1] = ind1;
    }
};

void _merge(float arr1[], int arr_in1[], int size1, float arr2[], int arr_in2[], int size2, float merged_arr[],
        int merged_ind[]){

    int i=0, j=0, k=0;

    while(k < size1+size2){
        if(i<size1 && j<size2){
            if(arr1[i] <= arr2[j]){
                merged_arr[k] = arr1[i];
                merged_ind[k] = arr_in1[i];
                i++;
                k++;
            }
            else{
                merged_arr[k] = arr2[j];
                merged_ind[k] = arr_in2[j];
                j++;
                k++;
            }
        }
        if(i<size1 && j==size2){
            merged_arr[k] = arr1[i];
            merged_ind[k] = arr_in1[i];
            i++;
            k++;
        }
        if(j<size2 && i==size1){
            merged_arr[k] = arr2[j];
            merged_ind[k] = arr_in2[j];
            j++;
            k++;
        }
    }
}

void merge_sort(float array[], int array_index[], int size){

    int run, split_count, range1, range2, range_mid;

    run = 2;
    split_count = 2;

    for(int i = 0;  i < size/split_count; i++){
        range1 = split_count*i;
        range2 = split_count*(i+1);
        if(range2 <= size){
            float pair_ordered[2];
            int pair_index_ordered[2];
            for(int j = range1; j < range2; j++){
                pair_ordered[j - range1] = array[j];
                pair_index_ordered[j - range1] = array_index[j];
            }

            _sort_pair(pair_ordered, pair_index_ordered);

            for(int j = range1; j < range2; j++){
                array[j] = pair_ordered[j - range1];
                array_index[j] = pair_index_ordered[j - range1];
            }
        }
    }

    while(((float)size)/((float)split_count) > 2.){
        split_count = _get_split_count(run);
        for(int i = 0; i < size/split_count; i++){
            range1 = 2*split_count*i;
            range2 = 2*split_count*(i+1);
            range_mid = 2*split_count*i + split_count;
            if(range2 > size){
                range2 = size;
            }
            if(range_mid > size){
                range_mid = size;
            }
            if(range_mid != range2){
                float array1[range_mid-range1], array2[range2-range_mid], arraym[range2-range1];
                int array_index1[range_mid-range1], array_index2[range2-range_mid], array_indexm[range2-range1];
                for(int j = 0; j < range_mid-range1; j++){
                    array1[j] = array[range1 + j];
                    array_index1[j] = array_index[range1 + j];
                }
                for(int j = 0; j < range2-range_mid; j++){
                    array2[j] = array[range_mid + j];
                    array_index2[j] = array_index[range_mid + j];
                }
                _merge(array1, array_index1, range_mid-range1, array2, array_index2, range2-range_mid, arraym,
                       array_indexm);
                for(int j = 0; j < range2-range1; j++){
                    array[range1 + j] = arraym[j];
                    array_index[range1 + j] = array_indexm[j];
                }
            }
        }
        run++;
    }
}
