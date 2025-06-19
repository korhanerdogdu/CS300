
#include <iostream>
#include <vector>
#include <sstream>

#include "AVLSEARCHTREE.h"

using namespace std;




// Function to split a string into words
void tokenize(const string& str, vector<string>& tokens) {
    stringstream ss(str);
    string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
}


// Struct to store document information
struct DocumentItem {
    string documentName;
    int count;

    // Constructor
    DocumentItem(const std::string& name, int cnt) : documentName(name), count(cnt) {}
};



// Struct to store word information
struct WordItem {
    string word;
    vector<DocumentItem> documents;

    // Constructor
    WordItem(const string& w) : word(w) {}
    
};






int main() {
    // AVLSearchTree örneği oluştur
    
    AVLSearchTree<string, WordItem*> myTree;  

    
    
    
    // Belge ve kelime örnekleri oluştur
    DocumentItem doc1("document1.txt", 3);
    DocumentItem doc2("document2.txt", 5);
    DocumentItem doc3("document3.txt", 2);

    WordItem* word1 = new WordItem("apple");
    word1->documents.push_back(doc1);
    word1->documents.push_back(doc2);

    WordItem* word2 = new WordItem("banana");
    word2->documents.push_back(doc3);

    
    
    // AVL ağacına kelime örneklerini ekle
    myTree.insert(word1->word, word1);
    
    myTree.insert(word2->word, word2);

    
    
    
    
    
    
    // "apple" kelimesinin belge listesini görüntüle
    WordItem* appleWord = myTree.find("apple");
    if (appleWord != nullptr) {
        cout << "Word: " << appleWord->word << std::endl;
        for (const auto& document : appleWord->documents) {
            cout << "Document Name: " << document.documentName << ", Count: " << document.count << std::endl;
        }
    } else {
        cout << "Word not found." << std::endl;
    }
    

    // "banana" kelimesinin belge listesini görüntüle
    WordItem* bananaWord = myTree.find("banana");
    if (bananaWord != nullptr) {
        cout << "Word: " << bananaWord->word << std::endl;
        for (const auto& document : bananaWord->documents) {
            cout << "Document Name: " << document.documentName << ", Count: " << document.count << std::endl;
        }
    } else {
        std::cout << "Word not found." << std::endl;
    }

    // Belleği temizle
    myTree.makeEmpty();

    // Bellek sızıntısını önlemek için kelime ve belge örneklerini sil
    delete word1;
    delete word2;

    return 0;
}
