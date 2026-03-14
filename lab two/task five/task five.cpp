#include <iostream>
#include <string>
using namespace std;

// Binary search implementation using templates 
template <typename T>
int binarySearch(T arr[], T value, int size) {
    int low = 0; // Initialize low to 0 
    int high = size - 1; // Initialize high to N-1 

    while (low <= high) { // Loop while low is less than or equal to high 
        int mid = (low + high) / 2; // Calculate middle index 

        // If middle element matches value, return index 
        if (arr[mid] == value) {
            return mid;
        }
        // If middle value is less than search value, ignore lower half 
        else if (arr[mid] < value) {
            low = mid + 1;
        }
        // If middle value is greater, ignore upper half 
        else {
            high = mid - 1;
        }
    }
    return -1; // Return -1 if not found 
}

// Helper function to display the search results 
template <typename T>
void printSearchResult(int index, T key) {
    if (index != -1) {
        cout << "Key '" << key << "' found at index: " << index << endl;
    }
    else {
        cout << "Key '" << key << "' not found." << endl;
    }
}

int main() {
    // Test with an integer array (sorted) of size 5 
    int intArray[5] = { 11, 12, 22, 25, 64 };
    int intKey = 22;
    int intIndex = binarySearch(intArray, intKey, 5);
    printSearchResult(intIndex, intKey);

    // Test with a float array (sorted) of size 4 
    float floatArray[4] = { 0.57f, 1.62f, 2.71f, 3.14f };
    float floatKey = 2.71f;
    int floatIndex = binarySearch(floatArray, floatKey, 4);
    printSearchResult(floatIndex, floatKey);

    // Test with a string array (sorted) of size 4 
    string stringArray[4] = { "apple", "banana", "grape", "orange" };
    string stringKey = "grape";
    int stringIndex = binarySearch(stringArray, stringKey, 4);
    printSearchResult(stringIndex, stringKey);

    return 0;
}