

// Korhan Erdoğdu 30838


#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;
#include "AVLSEARCHTREE.h"


// A function for making the word valid.
std::string cleanWord(const std::string& word) {
    std::string cleanedWord = word;

    cleanedWord.erase(std::remove_if(cleanedWord.begin(), cleanedWord.end(), ::ispunct), cleanedWord.end());

    std::transform(cleanedWord.begin(), cleanedWord.end(), cleanedWord.begin(), ::tolower);
    return cleanedWord;
}


// function reads the files and adds the words with their occurences to the vector.
void countWordOccurrences(const std::string& filename, std::vector<std::pair<std::string, int>>& wordOccurrences) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Cannot open the file: " << filename << std::endl;
        return;
    }

    std::string word;

    while (file >> word) {
        word = cleanWord(word);
        
  
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


// this will be appended to the WordItem node
struct DocumentItem {
    string documentName;
    int count;

    DocumentItem(const string& name, int cnt) : documentName(name), count(cnt) {}
};


struct WordItem {
    string word;
    vector<DocumentItem> documents;
    

    WordItem(const std::string& w) : word(w) {}
};




int main(){
    
    
    AVLSearchTree<string, WordItem> myTree;
    

    
    int numDocuments;
    cout << "Enter number of input files: "; // getting the document file names from the user

    cin >> numDocuments;
    
    
    
    vector<string> documentNames;  // vector for storing the document names.

  
    for (int i = 0; i < numDocuments; ++i) {
        
        string documentName;
        
        cout << "Enter " << i + 1 << ". file name: ";
        
        
        cin >> documentName;
        
        documentNames.push_back(documentName);
        
    }
    
    
    cin.ignore();  // if I dont do that a white space comes from the previos code and it causes problems.
    
    string getwords;
    bool addedonlyonce = false;
    bool input_check = true;
    
    
    while(input_check == true){
       
        
        cout << "Enter queried words in one line: ";
        
        
        // To fix the getline problem
        
        //cin.clear();
        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
    
        getline(cin, getwords);
        

        if(getwords == "ENDOFINPUT"){
            input_check = false;
            break;  // the while loop will end, automatically theprogram will end.
            
        
        }
        
        
        bool removed = false;  // when the word is removed; and after that we try to read the files again, the remove wont do its job because in the tree we still see the word that is trying to be removed.
        
        
        size_t indexx = getwords.find(" ");
        
        if(indexx != string::npos && getwords.substr(0,indexx - 0) == "REMOVE" ){ // if the first word is "remove", then remove the second word from the tree. the tree will automatically be balanced since it is a AVL tree.
            
            
            
            string the_word_to_be_removed = getwords.substr(indexx + 1, getwords.length() - 7  ); // 7 represents the length of remove + 1. It enables us to find
            
            
            
            // Transforming the word to the lower because we are transforming the words that are inside of the original file to lower.
            
            for (char &c : the_word_to_be_removed) {
                c = tolower(c);
            }
            
        
            myTree.remove(the_word_to_be_removed);
            
            
            
            cout << "word is removed" << endl;
            
            removed = true;
            
            
            continue;  // The program won't do the rest of the codes, it will ask "Enter queried words in one line".
            
            
        }
        
        
        //cout << "You entered: " << getwords << endl;
        
        
        // Turning each letter into lower.
        for (size_t i = 0; i < getwords.length(); ++i) {
            getwords[i] = std::tolower(getwords[i]);
        }
        
        size_t last_index = getwords.length()-1;
        
        vector<string> wordsinoneline; //lowered words.
        
        
        size_t index1 = getwords.find(' ');  // we are creating this for thinking there are at most 3 words to look for in one sentence
        
        size_t index2 = getwords.find(' ', index1 + 1);
        
        
        
        
        if (index1 != string::npos) {
            
            string word1 = getwords.substr(0, index1);  // second index --> how many steps
            
            wordsinoneline.push_back(word1);
            
            
            
    
            
            if (index2 != string::npos) {
                string word2 = getwords.substr(index1 + 1, index2 - index1 - 1);
                string word3 = getwords.substr(index2 + 1, last_index - index2);
                wordsinoneline.push_back(word2);
                wordsinoneline.push_back(word3);
                
            
            }
            
            else {
                
                
                string word2 = getwords.substr(index1 + 1,last_index );
                
                wordsinoneline.push_back(word2);
                
                
            }
            
        }
        
        else {
            
            string word1 = getwords;
            
            wordsinoneline.push_back(word1);
            
        }
        
        
        
        if(removed == false && addedonlyonce == false){ // ıf a word is planned to be removed, the below code shouldn't be executed because the below code reads the file and insert the words to the tree so the function of remove will be overriden because the eword that is planned to be removed is read from the file and inserted to the tree again. Similarly if it is also added, we shouldn't again read the file and add the words to our tree.
            
            bool is_the_first_file_checked = false;
            
            
            for(int k = 0; k< documentNames.size(); k ++ ){  // Read a one file and add the unique words to the file with their occurence.
                
                
                const string filename = documentNames[k];
                
                
                vector<pair<string, int>> wordOccurrences; // it will hold the word and the occurence in a file.
                
        
                countWordOccurrences(filename, wordOccurrences);  // the unique words are added to the pair with their values.
                    
                if(is_the_first_file_checked == false){  //only adding first file words to the tree, not the other file words. if we wouldn't use addonlyonce, first file words will be added to the tree again.
                    
                    for(int m = 0; m < wordOccurrences.size(); m ++){
                        
                        string name = wordOccurrences[m].first;  // it is a key to the node.
                        
                        int count = wordOccurrences[m].second;
                        
                        
                        DocumentItem documentitem(filename, count);  // documentitem  ---> "a.txt", 3  like that. for one word.
                        
                        
                        
                        
                        WordItem * word = new WordItem(name);
                        
                        word->documents.push_back(documentitem);
                        
                        myTree.insert(word->word, word);
                        

                        
                    }
                    
                    is_the_first_file_checked = true;
                    
                    

                }
                
                else{
                    // after the first file have been read, we only just add the document info to the tree. (We are not adding the words again.)
                    
                    
                    
                    for(int c = 0; c< wordOccurrences.size(); c++){
                        
                        
                        string name = wordOccurrences[c].first;  // it is a key to the node.
                        
                        int count = wordOccurrences[c].second;
                        
                        
                        if(myTree.find(name)!=NULL){
                            
                            DocumentItem docitem(filename,count);  // creating a new node that is going to be added to the tree as a document info.
                            
                            myTree.find(name)->documents.push_back(docitem);
                            
                        }
                        
 
                        
                    }
                    
                    
                    
                }
                
            }
            
            addedonlyonce = true; // for adding the values to the tree only once. Preventing from while loop.
            
            
        }
        

        // After all the documents have been read and the values added to the tress, we need to find the specific words from the tree.
        
        
        for(int k = 0; k < wordsinoneline.size(); k++){
            
            
            
            WordItem *foundnode;
            
            foundnode = myTree.find(wordsinoneline[k]);
            
            if(foundnode==NULL){
                
                
                
                cout << "No document contains the given query" << endl;
                //cout << "Word " << wordsinoneline[k] << " not found." << endl;
                
            }
            
            else {
                
                
                // printing the node items to the user
                
                for(int l=0; l < foundnode->documents.size();l++){
                    cout << "in Document " << foundnode->documents[l].documentName << ", " << wordsinoneline[k] << " found " << foundnode->documents[l].count << " times." << endl;
                    
                    
                    
                }
                
            }
            
        }
        
        
    }


}







