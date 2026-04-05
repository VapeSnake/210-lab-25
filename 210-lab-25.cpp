#include <iostream>
#include <vector>
#include <algorithm> // for sort function for vector.
#include <list>
#include <set>
#include <fstream>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace std::chrono;

int main() {
    vector<string> v;
    list<string> l;
    set<string> s;

    int vecReadDuration;
    int listReadDuration;
    int setReadDuration;

    ifstream inFile("words.txt");
    if (!inFile) { // check if file opened successfully
        cerr << "Unable to open file words.txt" << endl;
        return 1;
    }
// read words into vector and list, and time the operations, making sure to reset the file pointer back to the beginning of file.
    string word;
    auto start = high_resolution_clock::now(); // Starts the timer for reading into vector
    while (inFile >> word) {
        v.push_back(word);
    }
    auto end = high_resolution_clock::now();
    vecReadDuration = duration_cast<nanoseconds>(end - start).count();
    // This will be done between each container in each race.
    inFile.clear(); // Clear the EOF flag
    inFile.seekg(0); // Move the file pointer back to the beginning

    start = high_resolution_clock::now(); // Starts the timer for reading into list
    while (inFile >> word) {
        l.push_back(word);
    }
    end = high_resolution_clock::now();
    listReadDuration = duration_cast<nanoseconds>(end - start).count();
    inFile.clear();
    inFile.seekg(0);

    start = high_resolution_clock::now(); // Starts the timer for reading into set
    while (inFile >> word) {
        s.insert(word);
    }
    end = high_resolution_clock::now();
    setReadDuration = duration_cast<nanoseconds>(end - start).count();
    inFile.close(); // End of reading race between containers. May consider making functions for scalability.
// Begin sorting race.
    int vecSortDuration;
    int listSortDuration;
    int setSortDuration;
// Sort the vector using algorithm header since <vector> does not have a sort method built-in.
    auto sortStart = high_resolution_clock::now(); // Need different variables for each race to avoid confusion.
    sort(v.begin(), v.end());
    auto sortEnd = high_resolution_clock::now();
    vecSortDuration = duration_cast<nanoseconds>(sortEnd - sortStart).count();
// Sort the list using its built-in sort method.
    auto sortStart = high_resolution_clock::now();
    l.sort(); // Sort the list using its built-in sort method.
    auto sortEnd = high_resolution_clock::now();
    listSortDuration = duration_cast<nanoseconds>(sortEnd - sortStart).count();
// Set are automatically sorted.
    setSortDuration = -1; // Set to -1 since it is already sorted.
//Bdgin race for inserting "TESTCODE" in middle of each container, or into set.
    int vecInsertDuration;
    int listInsertDuration;
    int setInsertDuration;
// Insert "TESTCODE" into middle of vector using insert method.
    auto insertStart = high_resolution_clock::now();
    v.insert(v.begin() + v.size() / 2, "TESTCODE"); // Middle is found by dividing vector.size by 2. Pretty fast.
    auto insertEnd = high_resolution_clock::now();
    vecInsertDuration = duration_cast<nanoseconds>(insertEnd - insertStart).count();
// Insert "TESTCODE" into middle of list using insert method. Need to use an iterator to find the middle of the list.
    auto insertStart = high_resolution_clock::now();
    auto it = l.begin();
    advance(it, l.size() / 2); // Move the iterator to the middle of the list. Slower since it moves from beginning to middle.
    l.insert(it, "TESTCODE");
    auto insertEnd = high_resolution_clock::now();
    listInsertDuration = duration_cast<nanoseconds>(insertEnd - insertStart).count();




    return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/