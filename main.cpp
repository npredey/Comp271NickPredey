#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void bubble_sort (int arr[], int n);
void insertion_sort (int arr[], int length);
void shell_sort (int ar[], int length);
void QuickSort (int A[],int low, int high);
void MergeSort (int A[], int low, int high);
void Merge (int A[], int low, int high, int mid);
void ReadFile(string text_file, int myArray[]);
void Sort(string textfile);

int exc = 0;
int comp = 0;

int main()
{
    Sort("FewUnique.txt");
    Sort("NearlySorted.txt");
    Sort("Random.txt");
    Sort("Reversed.txt");
    cout << "Hello world!" << endl;
    return 0;
}

void bubble_sort (int arr[], int n)
{
    int counter;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            comp++;//a comparison is being made before this if statement
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                exc++; //because the if statement was satisfied
            }
        }
    }
}

void insertion_sort (int arr[], int length)
{
    int j, temp;
	for (int i = 0; i < length; i++){
		j = i;
		while (j > 0 && arr[j] < arr[j-1]){
		    temp = arr[j];
            arr[j] = arr[j-1];
            arr[j-1] = temp;
            j--;
            exc++;
            comp++;//an comparison and exchange is made each time the while loop is satisfied
        }
        comp++;// even when the while loop condition is not satisfied, the comparison is still made
    }
}

void shell_sort (int A[], int length)
{
    int temp, gap, i;
    int swapped;
    gap = length/2;
    do
    {
        do
        {
            swapped = 0;
            for(i = 0; i < length-gap; i++){
                comp++; //again, comparison is made before this conditional
                if (A[i] > A[i + gap]) {
                    temp = A[i];
                    A[i] = A[i+gap];
                    A[i+gap] = temp;
                    swapped = 1;
                    exc++;//an exchange was made because the if statement was satisfied
                }
            }
        }while (swapped == 1);
    } while ((gap = gap/2) >= 1);
}

void Swap (int &x, int &y)//basic swap function
{
    int temp;
    temp = x;
    x = y;
    y = temp;
}


 int Partition (int A[], int low, int high)
 {
     int j = low;
     int pivot = A[low];
     for (int i = low+1; i<= high; i++)
     {
         comp++;//a comparison is made before the if statement which is the first array element
         if (A[i] <= pivot)
         {
             j++;
             Swap (A[i],A[j]);
             exc++;//exchange made after the swap
         }
     }
     Swap (A[j],A[low]);
     exc++;// add an exchange because two numbers were swapped with the swap function
     return j;
 }

void QuickSort (int A[],int low, int high)
{
    int k;
    if (low < high)
    {
        k = Partition (A,low,high);
        QuickSort(A,low,k-1);
        QuickSort(A,k+1,high);
    }
}

void MergeSort (int A[], int low, int high)
{
    int mid;
    if (low < high)
    {
        mid = (low + high)/2;
        MergeSort(A,low,mid);
        MergeSort(A,mid+1,high);
        Merge(A,low,high,mid);
    }
}

void Merge (int A[], int low, int high, int mid)
{
    int i,j,k, C[10000];
    i = low;            //index for the first part
    j = mid +1;         //index for second part
    k = 0;              //index for array C
    while ((i <= mid) && (j <= high))       //merge arrays A & B in array C
    {
        comp++;// comparison is about to be made with the if statement
        if (A[i] < A[j]) {
            C[k] = A[i++];
            exc++;//exchange is being made because of the equal sign
        }
        else {
            C[k] = A[j++];
            exc++;//same as previous comment
        }
        k++;
    }
    while (i <=mid) {
        exc++;//exchange is made every time the while loop condition is satisfied
        C[k++] = A[i++]; }
    while (j <= high) {
        exc++; // same as previous comment
        C[k++] = A[j++]; }
    for (i = low, j =0; i <= high; i++, j++)        //copy array C contents back to array A
    {
        A[i] = C[j];
    }

}

void ReadFile(string text_file, int myArray[])
{
    ifstream in (text_file.c_str());
    if (in.is_open()) {
        for (int i = 0; i < 6; i++) //fill array with integers  from file
        {
            in >> myArray[i];
        }
    } else {
        cout << "File path is invalid." << endl;
    }
    in.clear();
    in.close();
}

void Sort(string textfile)
{
    cout << "For text file: " << textfile << endl;
    int a[10000];
    int bubble_sort_comparisons = 0;
    int bubble_sort_exchanges = 0;
    int insertion_sort_comparisons = 0;
    int insertion_sort_exchanges = 0;
    int shell_sort_comparsions = 0;
    int shell_sort_exchanges = 0;
    int merge_sort_exchanges = 0;
    int merge_sort_comparsions = 0;

    ReadFile(textfile, a);
    bubble_sort(a, 10000);

    bubble_sort_comparisons = comp;
    bubble_sort_exchanges = exc;
    exc = 0;
    comp = 0;

    ReadFile(textfile, a);
    insertion_sort(a, 10000);

    insertion_sort_comparisons = comp;
    insertion_sort_exchanges = exc;
    exc = 0;
    comp = 0;

    ReadFile(textfile, a);
    shell_sort(a, 10000);

    shell_sort_comparsions = comp;
    shell_sort_exchanges = exc;
    exc = 0;
    comp = 0;

    ReadFile(textfile, a);
    MergeSort(a, 0, 9999);
    merge_sort_comparsions = comp;
    merge_sort_exchanges = exc;
    exc = 0;
    comp = 0;

    ReadFile(textfile, a);
    QuickSort(a, 0, 9999);

    cout << "Quick sort comparisons: " << comp << endl;
    cout << "Quick sort exchanges: " << exc << endl;
    exc = 0;
    comp = 0;

    cout << "Merge sort comparisons: " << merge_sort_comparsions << endl;
    cout << "Merge sort exchanges: " << merge_sort_exchanges << endl;

    cout << "Shell sort comparisons: " << shell_sort_comparsions << endl;
    cout << "Shell sort exchanges: " << shell_sort_exchanges << endl;

    cout << "Insertion sort comparisons: " << insertion_sort_comparisons << endl;
    cout << "Insertions sort exchanges: " << insertion_sort_exchanges << endl;

    cout << "Bubble sort comparisons: " << bubble_sort_comparisons << endl;
    cout << "Bubble sort exchanges: " << bubble_sort_exchanges << endl;
    cout << "\n";


}
