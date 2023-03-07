#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

void swap(int *vec1, int *vec2);
void insertion_sort(vector <int> &vec, int size);
vector<int> merge_sort(vector<int> vec);
vector<int> merge(vector<int> vecOne, vector<int> vecTwo);
void quicksort(vector <int> &vec, int low, int high);
int partition(vector <int> &vec, int low, int high);


void swap(int *vec1, int *vec2)
{
    //swaps the order of two values in a vector.
    int temp = *vec2;
    *vec2 = *vec1;
    *vec1 = temp;
}

void insertion_sort(vector <int> &vec, int size)
{   

    /*compare vec[i] with all of the values before it and swap until all the items in the vector 
    are in sequential order up to i*/

    for( int i = 1; i < size; i++)
    {
        int j = i;
        while( j>0 && vec[j-1] > vec[j])
        {
            swap(&vec[j], &vec[j-1]);
            j = j-1;
        } 
    }
}


vector<int> merge_sort(vector<int> vec)
{
    //subdivides the vector until each split vector is down to one element

    int n = vec.size();

    if (n == 1) //base case
        return vec;

    vector<int> subVec_one(vec.begin(), vec.begin() + vec.size() / 2);  //subVec_one is the first half of og vector
    vector<int> subVec_two(vec.begin() + vec.size() / 2, vec.end()); //subVec_two is the second half of og vector

    subVec_one = merge_sort(subVec_one); // subdivided vector gets split again through recursion
    subVec_two = merge_sort(subVec_two);

    return merge(subVec_one, subVec_two);   //subdivided arrays gets put into function merge to be sorted and merged
}


vector<int> merge(vector<int> vecOne, vector<int> vecTwo)
{
    vector<int> vecThree; //final sorted array

    while (vecOne.size() > 0 && vecTwo.size() > 0) //loop runs as long as both vectors are not empty
    {
        if (vecOne[0] > vecTwo[0]) //stores the smaller value between vecOne[0] and vecTwo[0] into vecThree
        {
            vecThree.push_back(vecTwo[0]); //if vecOne[0] > vecTwo[0], vecTwo[0] stored in vecThree 
            vecTwo.erase(vecTwo.begin()); //vecTwo[0] erased from vecTwo
        }
        else
        {
            vecThree.push_back(vecOne[0]); //else vecOne[0] stored in VecThree
            vecOne.erase(vecOne.begin());  //vecOne[0] gets erased
        }
    }

    //appends each value of vecOne into vecThree and erases those values from vecOne
    while (vecOne.size() > 0)
    {
        vecThree.push_back(vecOne[0]);
        vecOne.erase(vecOne.begin());
    }

    //appends each value of vecTwo into vecThree and erases those values from vecTwo
    while (vecTwo.size() > 0)
    {
        vecThree.push_back(vecTwo[0]);
        vecTwo.erase(vecTwo.begin());
    }

    //returns vecThree the sorted vector
    return vecThree;
}


// Quicksort algorithm implementation that sorts a vector of integers
// using a pivot element to partition the vector into two subvectors
// and then recursively sorts those subvectors.

void quicksort(vector <int> &vec, int low, int high) 
{
    // Check if there is more than one element to sort.
    if(low < high)
    {
        // Select a pivot element and partition the vector.
        int pivot_location = partition(vec, low, high);
        
        // Recursively sort the left subvector.
        quicksort(vec, low, pivot_location);
        
        // Recursively sort the right subvector.
        quicksort(vec, pivot_location+1, high);
    }
}

// Partition function that selects a pivot element and partitions
// the vector into two subvectors, one with elements smaller than
// the pivot and one with elements greater than the pivot.

int partition(vector <int> &vec, int low, int high)
{
    // Select the pivot element (in this implementation, the first element).
    int pivot = vec[low];
    
    // Initialize the left wall to the pivot element.
    int leftwall = low;

    // Iterate through the vector and partition it based on whether
    // each element is smaller or greater than the pivot.
    for(int i = low+1; i <= high; i++)
    {
        if(vec[i] < pivot)
        {
            // Swap the current element with the element immediately
            // to the right of the left wall and move the left wall
            // one position to the right.
            swap(&vec[i], &vec[leftwall]); 
            leftwall = leftwall+1;
        }
    }

    // Swap the pivot element with the element at the left wall, which
    // puts the pivot in its final sorted position in the vector.
    swap(&pivot, &vec[leftwall]);

    // Return the index of the pivot element in the sorted vector.
    return(leftwall);
}



int main() {
    srand(time(NULL));
    vector<int> Vecinsertion_sort;
    vector<int> Vecquick_sort;
    vector<int> Vecmerge_sort;


    /*number of numbers that will be sorted
     change NUMBERS_SIZE0 to see how long it will take each sorting algorithm to 
    sort the vector as NUMBERS_SIZE0 changes*/
    int NUMBERS_SIZE0 = 100;
    


    for (int i = 0; i < NUMBERS_SIZE0; i++)
    {
        int x = rand() % 5000 + 1;
        Vecinsertion_sort.push_back(x);
        Vecquick_sort.push_back(x);
        Vecmerge_sort.push_back(x);
    }
    


    auto start = chrono::high_resolution_clock::now();
    insertion_sort(Vecinsertion_sort, NUMBERS_SIZE0);
    auto stop = chrono::high_resolution_clock::now();
    auto IS_duration1 = chrono::duration_cast<chrono::microseconds>(stop - start);
  



    start = chrono::high_resolution_clock::now();
    quicksort(Vecquick_sort,0, NUMBERS_SIZE0 - 1);
    stop = chrono::high_resolution_clock::now();
    auto QS_duration1 = chrono::duration_cast<chrono::microseconds>(stop - start);



    start = chrono::high_resolution_clock::now();
    Vecmerge_sort = merge_sort(Vecmerge_sort);
    stop = chrono::high_resolution_clock::now();
    auto MS_duration1 = chrono::duration_cast<chrono::microseconds>(stop - start);


    // UNCOMMENT TO SEE SORTED NUMBERS
    // cout << "Insertion Sort" << endl;
    // for(int i = 0; i < NUMBERS_SIZE0; i++)
    // {
    //     cout << Vecinsertion_sort[i] << " ";
    // }
    // cout << endl << endl;

    // cout << "Quick Sort" << endl;
    // for(int i = 0; i < NUMBERS_SIZE0; i++)
    // {
    //     cout << Vecquick_sort[i] << " ";
    // }
    // cout << endl<<endl;

    //     cout << "Merge Sort" << endl;
    // for(int i = 0; i < NUMBERS_SIZE0; i++)
    // {
    //     cout << Vecmerge_sort[i] << " ";
    // }
    // cout << endl <<endl;

    cout << endl << "Time taken for insertion sort: " << IS_duration1.count() << " microsecond(s)" << endl;
    cout << endl << "Time taken for quick sort: " << QS_duration1.count() << " microsecond(s)" << endl;
    cout << endl << "Time taken for merge sort: " << MS_duration1.count() << " microsecond(s)" << endl;
 
}

