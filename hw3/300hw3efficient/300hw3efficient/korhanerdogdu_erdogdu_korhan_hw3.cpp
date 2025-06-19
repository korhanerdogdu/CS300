
//Korhan Erdoğdu 30383


#include <iostream>
#include <sstream>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>



#include "HashTable.h"
#include "BinarySearchTree.h"
#include "strutils.h"


using namespace std;


// A function for making the word valid.
std::string clean_Word(const std::string& word) {
    
    std::string cleanedWord = word;

    cleanedWord.erase(std::remove_if(cleanedWord.begin(), cleanedWord.end(), ::ispunct), cleanedWord.end());

    std::transform(cleanedWord.begin(), cleanedWord.end(), cleanedWord.begin(), ::tolower);
    return cleanedWord;
}



// function reads the files and adds the words with their occurences to the vector.
void count_Word_Occurrences(const std::string& filename, std::vector<std::pair<std::string, int>>& wordOccurrences) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Cannot open the file: " << filename << std::endl;
        return;
    }

    std::string word;

    while (file >> word) {
        word = clean_Word(word);
        
  
        auto it = std::find_if(wordOccurrences.begin(), wordOccurrences.end(),
                               [word](const std::pair<std::string, int>& info) { return info.first == word; });

        if (it != wordOccurrences.end()) {
 
            it->second++;
        } else {

            wordOccurrences.push_back({word, 1});
        }
    }
    
    
    file.clear();
    file.seekg(0, std::ios::beg);
    
}


struct WordItem
{
    string word;
    vector<string> info;
    
};

struct DocumentItem {
    
    string documentName;
    int count;
    
};



// HERE

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



int main()
{
    

    
    
    
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
    
    string userInput;
    getline(cin, userInput);  // Read the entire line of user input
    
    istringstream wordStream(userInput);  // Stream to process each word

    
    
    string currentWord = "";
    
    
    vector<WordItem> bstData, hashTableData;  // for storing the nodes, in other words(i.e) the string name and the file info in one nıde as an index of the vector.
    

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
            
            
            
            
            /*
             
             
             vector<WordItem> & bst_node_vector, vector<WordItem> & hash_node_vector, string & currentstring, long int & binarysearchtreeTime, long int & hashTableTime
             
             */
            if (!currentWord.empty()) {
                
                
                time_calculating_while_adding_nodes(bstData,hashTableData, currentWord, bstTime , hashTableTime );
                
                
                currentWord.clear();
                
            }
            
        }
        
    }
    
    // Process the last word if present
    if (!currentWord.empty()) {
        
        time_calculating_while_adding_nodes(bstData,hashTableData, currentWord, bstTime , hashTableTime );

    }

    
    bool wordExists;
    int missingWordCount = 0;

    for (const string& filename : filenames) {
        
        wordExists = false;
        string bstOutput = print_word_info(filename, bstData, wordExists);
        
        if (wordExists) {
            
            cout << bstOutput << endl;
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

    for (const string& filename : filenames) {
        
        wordExists = false;
        string hashOutput = print_word_info(filename, hashTableData, wordExists);
        
        if (wordExists) {
            
            cout << hashOutput << endl;
        }
        
        else {
            
            missingWordCount++;
        }
        
    }
    
    
    // If none of the files contain any of the queried words
    if (missingWordCount == filenames.size()) {
        
        cout << "No document contains the given query" << endl;
    }


    cout << "\nTime: " << bstTime << "\n"; //indicates the total time taken by Binary Search Tree
    cout << "\nTime: " << hashTableTime << "\n"; //indicates the total time taken by Hash table
    cout << "Speed Up: " << static_cast<double>(bstTime) / hashTableTime << endl;
    // we understand that hash table is much more faster than bst.
    
    return 0;
    
}


