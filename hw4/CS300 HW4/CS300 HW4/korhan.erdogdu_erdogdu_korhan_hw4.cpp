
//(I AM USİNG XCODE)

//Korhan Erdoğdu 30383

#include <iostream>
#include <sstream>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include <random> // for randomly selecting the pivot in the quick sort

#include "HashTable.h"
#include "BinarySearchTree.h"
#include "strutils.h"

using namespace std;


struct WordItem
{
    string word;
    vector<string> info;
    
};


struct DocumentItem {
    
    string documentName;
    int count;
    
};


BinarySearchTree<string> binarysearchtree("no_existing_item"); // i.e -->  there is no specific word in the binary search tree

HashTable<string> hashtable("no_existing_item");  // i.e -->  there is no specific word in the hash table.


void increase_occurence_in_file(string &doc_info) {  // we will update the document info.
    
    // Find the positions of the comma and the closing brace
    size_t commaPos = doc_info.find(",");
    size_t bracePos = doc_info.find("}");
    
    // Extract the number part of the string
    string numberPart = doc_info.substr(commaPos + 2, bracePos - commaPos - 2);

    // Convert the number part to an integer, increment it, and convert back to string
    int number = stoi(numberPart);
    number++;
    string incrementedNumber = to_string(number);

    // Rebuild the info string with the incremented number
    doc_info = doc_info.substr(0, commaPos + 2) + incrementedNumber + "}";
}



/*
 If the word is new, it adds it with initial info. If the word exists, it updates the info, either by adding new file info or incrementing the count for an existing file.
 */


void adding_each_word(string &currentstring, const string &filename) {
    
    if (!currentstring.empty()) {
        // Check if the word exists in the BST
        
        if (binarysearchtree.find(currentstring) == "no_existing_item") {
            // Word not found, insert it with initial count
            
            
            string doc_info = "{ " + filename + ", 1 }";  // we will add new word
            
            
            binarysearchtree.insert(currentstring);
            hashtable.insert(currentstring);
            
            binarysearchtree.update_document_info(currentstring, doc_info, true);
            hashtable.update_document_info(currentstring, doc_info, true);
            
            
        }
        
        else {
            
            // Word found, update the count or information
            
            string info = hashtable.final_Doc_info_in_specific_file_for_word(currentstring);  // finding the latest document info of the word in a specific file. ie. korhan is {“a.txt”, 1}. we will convert it to the {“a.txt”, 2}. this code gives us something like {“a.txt”, 18}.
            
            size_t commaPos = info.find(",");
            string fileInInfo = info.substr(2, commaPos - 2);  // getting the filename.

            if (fileInInfo != filename) {
                // New file for the word, insert new info
                
                string newFileEntry = "{ " + filename + ", 1 }";
                binarysearchtree.update_document_info(currentstring, newFileEntry, true);
                hashtable.update_document_info(currentstring, newFileEntry, true);
            }
            
            
            
            else {
                
                
                // Existing file, increment the count
                increase_occurence_in_file(info);
                binarysearchtree.update_document_info(currentstring, info, false); // update_document_info
                hashtable.update_document_info(currentstring, info, false);
                
            }
        }
        
        currentstring.clear();
    }
}



// Helper function to extract count from the information string
int extractCount(const string &info) {
    size_t startPos = info.find_last_of(',') + 2;
    size_t endPos = info.find_last_of('}');
    string countStr = info.substr(startPos, endPos - startPos);
    return stoi(countStr);
}



void time_calculating_while_adding_nodes(vector<WordItem> & bst_node_vector, vector<WordItem> & hash_node_vector, string & currentstring, long int & binarysearchtreeTime, long int & hashTableTime){
    
    
    
    string no_item = "";
    
    if(currentstring != no_item){
        
        WordItem bst_worditem;
        WordItem hash_worditem;
        
        
        
        bst_worditem.word = currentstring;
        hash_worditem.word = currentstring;
        
        
        vector<string> bst_document;
        vector<string> hash_document;
        
        
        
        int k = 100;
        
        
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < k; i++){
            
            if (binarysearchtree.find(currentstring) != "no_existing_item"){
                
                
                bst_document = binarysearchtree.doc_infos(currentstring); //this search operation will helps us to understand which data structure is more efficient to use, because the time difference is coming from this operation. (returning the document vector that has a specific string)
                
                
            }
        }
        
        
        auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
        
        
        binarysearchtreeTime = binarysearchtreeTime + BSTTime.count() / k;
        
        bst_worditem.info = bst_document;
        
        bst_node_vector.push_back(bst_worditem); // // after the search of a specific key's info, we add the word itself and its corresponding info i.e ({{“a.txt”, 1}, {“b.txt”, 4}}.) to the vector.
        //The method can be used to compare the search performance of different data structures, such as BSTs and hash tables. By measuring and comparing the time it takes to search for the same set of words in different structures.
        

    
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < k; i++){
            
            if (hashtable.find(currentstring) != "no_existing_item"){
            
                
                hash_document = hashtable.return_document_vector(currentstring); //this search operation will helps us to understand which data structure is more efficient to use, because the time difference is coming from this operation. it return the document vector.
                
                
            }
            
        }
        
        
        
        auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
        
        hashTableTime = hashTableTime + HTTime.count() / k;
        
        hash_worditem.info = hash_document;  // asigning the vector.
        
        hash_node_vector.push_back(hash_worditem); // after the search of a specific key's info, we add the word itself and its corresponding info i.e ({{“a.txt”, 1}, {“b.txt”, 4}}.) to the vector.
        //The method can be used to compare the search performance of different data structures, such as BSTs and hash tables. By measuring and comparing the time it takes to search for the same set of words in different structures.
        
    
        
    }
    
}





string print_word_info(const string& filename, const vector<WordItem>& full_of_nodes_bst_or_hash, bool& wordFoundInDocument) {
    
   
    wordFoundInDocument = false;
    string output = "in Document " + filename;
    
    
    
    bool checkk = true;
    for (const auto& wordInfo : full_of_nodes_bst_or_hash) {
        
        for (const auto& info : wordInfo.info) {
            
            size_t commaPos = info.find(",");
            string fileInInfo = info.substr(2, commaPos - 2);

            if (fileInInfo == filename) {
                
                string count = info.substr(commaPos + 2, info.length() - commaPos - 3);
                output += ", " + wordInfo.word + " was found " + count + " times";
                
                   
                    
                    
        
                
                wordFoundInDocument = true;
                
            }
        }
        
        
        
    }
    
    

    if (!wordFoundInDocument) {
        return "No document contains the given query";
    }

    return output + ".";
}


/*

 For the above,
 
 The function checks each word in the everything vector to see if it appears in the specified file.

 If it does, the function constructs a string indicating how many times each word was found in that file.

 If none of the words were found in the file, it returns a message stating that no document contains the given query.
 
 */






template <class Object>
void binary_search(vector<Object>& list, string & key, string & printme) // binary search algorithm
{
    
    int mid, high = list.size()-1, low = 0;
    bool flag = true;
    while (low <= high && flag)
    {
        mid = (low + high)/2;
        if (list[mid] == key)
        {
            int prev = mid;
            while (list[prev] == key)
            {
                prev --;
            }
            prev ++;
            while (list[prev] == key)
            {
                contactPrint(list[prev], printme);
                prev ++ ;
            }
            flag = false;
        }
        else if (list[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
}




// Binary search function
template <class Object>
int binarySearchalgorithm(const vector<Object>& arr, const string& target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Check if target is present at mid
        if (arr[mid] == target) {
            return mid;
        }

        // If target is greater, ignore the left half
        else if (arr[mid] < target) {
            left = mid + 1;
        }

        // If target is smaller, ignore the right half
        else {
            right = mid - 1;
        }
    }

    // Target not present in the array
    return -1;
}




inline int leftChild( int i )
{
    return 2*i+1;
}




template <class Object>
void percDown( vector<Object> & a, int i, int n ) // helper function
{
    int child;
    Object tmp;
    
    for (tmp=a[i] ; leftChild(i) < n; i = child )
    {
        child = leftChild(i);
        if ( child != n-1 && a[ child  ] < a[ child+1 ] )
            child++;
        if ( a[child ] > tmp )
            a[i] = a[ child ];
        else
            break;
    }
    a[ i ] = tmp;
}






template <class Object>
void heap_Sort(vector<Object> & a)
{
    for (int i = a.size()/2; i >=0; i--)
        percDown(a, i, a.size());
    for (int j = a.size() -1; j >0; j--)
    {
           swap(a[0], a[j]);    // swap max to the last pos.
          percDown(a, 0, j); // re-form the heap
    }
}





template <class Object>
void insertion_Sort( vector<Object> & a, int left, int right )
{ //only sorting from the left index to the right index
    for ( int p = left + 1; p <= right; p++ )
    {
        Object tmp = a[ p ];
        int j;
        
        for ( j = p; j > left && tmp < a[ j - 1 ]; j-- )
            a[ j ] = a[ j - 1 ];
        a[ j ] = tmp;
    }
}






template <class Object>
inline void swapp( Object & obj1, Object & obj2 )
{
     Object tmp = obj1;
     obj1 = obj2;
     obj2 = tmp;
}




template <class Object>
const Object & mediann( vector<Object> & a, int left, int right )
 {
       int center = ( left + right ) / 2;
       if ( a[ center ] < a[ left ] )
         swap( a[ left ], a[ center ] );
       if ( a[ right ] < a[ left ] )
         swap( a[ left ], a[ right ] );
       if ( a[ right ] < a[ center ] )
         swap( a[ center ], a[ right ] );

       swap( a[ center ], a[ right - 1 ] );
       return a[ right - 1 ];
 }





template <class Object>
void quick_sort(vector<Object>& a, int left, int right, const string& pivotType) {
    
    if (left < right) {
        Object pivot;
        
        if (pivotType == "first") {
            pivot = a[left];
            
        }
        
        else if (pivotType == "random") {
            
            srand(time(nullptr));
            int randomIndex = left + rand() % (right - left);
            pivot = a[randomIndex];
            swapp(a[randomIndex], a[right]); // Move pivot to end
        }
        
        
        
        else if (pivotType == "median") {
            
            
            pivot = mediann(a, left, right);
        }
                
        
        if(left + 10 <= right){
            
            int i = left, j = right - 1;
            for ( ; ; )
            {
                while ( a[ ++i ] < pivot ) { }
                
                while ( pivot < a[ --j ] ) { }
                
                if ( i < j )
                    swapp( a[ i ], a[ j ] );
                else
                    break;
            }
            swapp( a[ i ], a[ right - 1 ] );
            quick_sort( a, left, i - 1 ,pivotType);
            quick_sort( a, i + 1, right,pivotType );
            
            
        }
        
        else{
            
            insertion_Sort( a, left, right);
        }
        

    }
}


// Call this function with pivotType as "first", "random", or "median"

 
 
template <class Object>
void merge(vector<Object> & a, int left, int center, int right) // modified to not allocate new memory
{
    int start = center + 1;
    if (a[center] <= a[start])
        return;
 
    while (left <= center && start <= right)
    {
        if (a[left] <= a[start]) {
            left++;
        }
        else
        {
            Object info = a[start];
            int idx = start;
            
            while (idx != left) {
                a[idx] = a[idx - 1];
                idx--;
            }
            a[left] = info;
            left++;
            center++;
            start++;
        }
    }
}


template <class Object>
void merge_Sort(vector<Object> & a, int left, int right)
{
    if (left < right)
    {
        int center = (left + right) / 2;
        merge_Sort(a, left, center);
        merge_Sort(a, center + 1, right);
        merge(a, left, center, right);
    }
}




//Every non-alphabetical character is considered as a separator. This rule applies for both the text in input files and queried words. This function is for adding the structured files( non-alphabetical character is considered as a separator and uppercase letters turn to lowercase letters) to the vectors one by one. After that, we will combine all the vectors and sort the combined vector. Therefore, we will be able to make binary search on the combined vector.

vector<string> processFile(const string& filename) {  // it will not change the original file. because we use ifstream.
    
    vector<string> words;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        
        for (char &c : line){
            
            
            if (!isalpha(c)) {
                
                c = ' '; // Replace non-alphabetical characters with space
            }
            
            else if (isupper(c)) {
                
                c = tolower(c); // Convert uppercase to lowercase
                
            }
        }
        istringstream iss(line);
        string word;
        while (iss >> word) {
            words.push_back(word);
            
        }
        
    }

    return words;
}



int main(){
    
    
    
    vector<string> combined_to_be_sorted;
    
    
    
    string currentstring = "";
    int numoffiles;
    string filename;
    
    
    cout << "Enter number of input files: ";
    cin >> numoffiles;
    

    
    ifstream input;
    char character;
    
    vector<string> filenames; //vector that has all the file names
    
    
    for(int i = 0; i < numoffiles; i ++){
        
        cout << "Enter " << i + 1 << ". file name: ";
        cin >> filename;
        filenames.push_back(filename);
    
    }
    
    
    for(int i = 0; i < numoffiles; i ++){  // this loop is for converting the uppercase letters to lowercase, if caught a non-letter it will be understood that it is the end of the word and the word will be sent to the function.
        
        
        filename = filenames[i];
        input.open(filename.c_str());
        
        
        vector<string> sortedvector_forthefile;
        sortedvector_forthefile = processFile(filename);
        
        
        for(int p = 0; p< sortedvector_forthefile.size();p++){
            
            combined_to_be_sorted.push_back(sortedvector_forthefile[p]);
            
        }
        
        // we are reading the files again to insert the modified words to hash table and binary tree.
        
        while(input.get(character)){  // search the characters in the line one by one.
            

            
            if (isupper(character)) { // converting the uppercase letter to the lowercase.
                character = character - ('A' - 'a');
            }
            
            
            
            if (islower(character)) {
                currentstring += character;
            }
            
            else{
                
                adding_each_word(currentstring, filename); // if the there is no character that we are at the index, the current string will be sent to the function to be processed. The currentstring might be a word or just an only character. (End of the word or character.)
            }
        
        }
        
        
        input.close();
        
        
        
    }
    
    adding_each_word(currentstring, filename); //adding the last word after escaping the loop
    

    
    hashtable.loadfactor_wordcount_info(); //prints the current load factor and the amount of words in the table
    

    cin.ignore();
    
    cout << "Enter queried words in one line: ";
    
    string copyinputforbinarysearch;
    string userInput;
    getline(cin, userInput);  // Read the entire line of user input
    
    copyinputforbinarysearch = userInput;
    
    istringstream wordStream(userInput);  // Stream to process each word

    string currentWord = "";
    
    vector<WordItem> bstData, hashTableData;  // for storing the nodes, in other words(i.e) the string name and the file info in one node as an index of the vector.
    
    long int bstTime = 0, hashTableTime = 0;  // Initialize timers
    char currentChar;

    
    while (wordStream.get(currentChar)) {
        
        
        if (isupper(currentChar)) { // Convert uppercase to lowercase
            
            
            
            currentChar = tolower(currentChar);
        }
        
        
        
        
        
        if (islower(currentChar)) { // If it's a lowercase letter
            
            
            currentWord += currentChar;

        }
        
        
        else {  // if our character nor lower or upper, such as it is a blank space, coma or dot; we will do the following code:
            
            if (!currentWord.empty()) {
                
                
                time_calculating_while_adding_nodes(bstData,hashTableData, currentWord, bstTime , hashTableTime );
                // gives how much time spent in bst and hash operations.
                
                currentWord.clear();
                
            }
            
        }
        
    }
    
    // Process the last word if present
    if (!currentWord.empty()) {
        
        time_calculating_while_adding_nodes(bstData,hashTableData, currentWord, bstTime , hashTableTime );
        // gives how much time spent in bst and hash operations.
        

    }
    
    bool wordExists;
    int missingWordCount = 0;

    bool printcheck = true;
    
    for (const string& filename : filenames) {
        
        wordExists = false;
        string bstOutput = print_word_info(filename, bstData, wordExists);
        
        
        
        if (wordExists) {
            
            cout << bstOutput << endl;
        
            if(printcheck == true ){  // NEW
                cout << bstOutput << endl;
                printcheck = false;
            }
            
        }
        else {
            
            missingWordCount++;
        }
        
    }
    
    
    // If none of the files contain any of the queried words
    if (missingWordCount == filenames.size()) {
        
        cout << "No document contains the given query" << endl;
    }

    
    // Reset for hash table analysis
   
    missingWordCount = 0;
    bool printcheck2 = true;
    
    for (const string& filename : filenames) {
        
        wordExists = false;
        string hashOutput = print_word_info(filename, hashTableData, wordExists);
        
        if (wordExists) {
            
            cout << hashOutput << endl;
            
            /*
            if(printcheck2 == true ){  // NEW
                cout << hashOutput << endl;
                printcheck2 = false;
            }
             */
            
        }
        
        else {
            
            missingWordCount++;
        }
        
    }
    
    
    // If none of the files contain any of the queried words
    if (missingWordCount == filenames.size()) {
        
        cout << "No document contains the given query" << endl;
    }
    
    
    for (char &c : copyinputforbinarysearch){
        if (!isalpha(c)) {
            
            c = ' '; // Replace non-alphabetical characters with space
        }
        else if (isupper(c)) {
            
            c = tolower(c); // Convert uppercase to lowercase
        }
    }
    
    vector<string> copyinputwords;
    istringstream iss(copyinputforbinarysearch);
    string copyinputword;

    while (iss >> copyinputword) {
        copyinputwords.push_back(copyinputword);
    }


    
    cout << "\nBinary Search Tree Time: " << bstTime << "\n"; //indicates the total time taken by Binary Search Tree
    cout << "Hash Table Time: " << hashTableTime << "\n"; //indicates the total time taken by Hash table
    
    // we understand that hash table is much more faster than bst.
    
    

    vector<string> uniqueVector;

    // Check and insert only unique elements into the vector
    for (const auto& str : combined_to_be_sorted) {
        if (find(uniqueVector.begin(), uniqueVector.end(), str) == uniqueVector.end()) {
            uniqueVector.push_back(str);
        }
    }
    // Overwriting the original vector with unique elements
    combined_to_be_sorted = move(uniqueVector);  // it is not sorted.
    
    
    
    vector<string> binarysearchhh_vec = combined_to_be_sorted;
    vector<string> qs_vec = combined_to_be_sorted;
    vector<string> is_vec = combined_to_be_sorted;
    vector<string> ms_vec = combined_to_be_sorted;
    vector<string> hs_vec = combined_to_be_sorted;  // we are creating copy of the vector for applying different sort methods.
    int vectorsize = combined_to_be_sorted.size()-1; // to get the index
    
    
    // for binary search first we need to sort the vector. Let's sort with meadian quick sort, after that we can search for a specific string.
    
    quick_sort(binarysearchhh_vec, 0, vectorsize, "median");
    
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 100; i++){
        
        for(int p = 0 ; p < copyinputwords.size(); p ++){  // these are the words of indexes that comes from the query. We will try to find each of them in a sorted array by doing binary search. The query is also organized, fixed in the previous codes.
            
            
            string a_word = copyinputwords[p];
            int found_at_this_index = binarySearchalgorithm(binarysearchhh_vec, a_word);
            
            
        }
    }
    auto endd = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
    
    double binarysearchtime= endd.count() / 100;
    
    
    cout << "Binary Search Time: " << binarysearchtime << endl << endl;
    
    
    //  Quick Sort (selection of pivot=first, pivot=random, and pivot=median)
    
    ///pivot=median

    int k = 100;
    clock_t begin_time;

    
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++){
        
        quick_sort(qs_vec, 0, vectorsize, "median");
    }
    endd = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
    
    double qsm= endd.count() / k;
    
    std::cout << "Quick Sort(median) Time: " << endd.count() / k << "\n";
    
    

    /// pivot=random
  
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++){
        
        quick_sort(qs_vec, 0, vectorsize, "random");
    }
    endd = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
    
    double qsr= endd.count() / k;
    
    std::cout << "Quick Sort(random) Time: " << endd.count() / k << "\n";
    
    
    
    ///pivot=first
    
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 5; i++){  // if the pivot is in the first index, it will consume lots pf time and additionally if we set the k value to 100, it will consume enourmous amount of time and program crashes. Therefore I selected a k value smaller than 100 to prevent crashing. it will also be larger than other quicksorts.
        
        quick_sort(qs_vec, 0, vectorsize, "first");
    }
    
    
    endd = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
    
    double qsf= endd.count() / k;
    
    std::cout << "Quick Sort(first) Time: " << endd.count() / k << "\n";
    

    
    
    // Merge Sort (in-place: without using extra memory storage)
    
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++){
        
        merge_Sort(ms_vec, 0, vectorsize);
    }
    
    
    endd = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
    
    double ms = endd.count() / k;
    
    std::cout << "Merge Sort Time: " << endd.count() / k << "\n";
    


    
    // Heap Sort
    
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++){
        
        heap_Sort(hs_vec);
    }
    
    endd = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
    
    double hs= endd.count() / k;
    
    std::cout << "Heap Sort Time: " << endd.count() / k << "\n";
    
    
    
    
    // Insertion Sort
    
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++){
        
        insertion_Sort(is_vec, 0, vectorsize);
    }
    
    endd = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
    
    double is = endd.count() / k;
    
    cout << "Insertion Sort Time: " << endd.count() / k << "\n" << endl;
    
    cout << "Speed Up BST/HST: " << static_cast<double>(bstTime) / hashTableTime<< endl;
    
    cout << "Speed Up Merge Sort/Quick Sort(Median): " << static_cast<double>(ms / qsm) << endl;
    
    cout << "Speed Up Heap Sort/Quick Sort(Median): " <<static_cast<double>(hs) / qsm << endl;
    
    cout << "Speed Up Insertion Sort/Quick Sort(Median): " << static_cast<double>(is) / qsm << endl << endl;
    
    cout << "Speed Up Binary Search / Binary Search Tree Time: " << static_cast<double>(binarysearchtime) / bstTime << endl;
    
    cout << "Speed Up Binary Search / Hash Table Time: " <<  static_cast<double>(binarysearchtime) / hashTableTime << endl;
    
    return 0;
    

}




