
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>

using namespace std;

// Düğüm yapısını tanımla
struct Node {
    string word;
    map<string, int> fileCounts; // Kelimenin dosyalardaki sayısını tutan map

    Node(string w) : word(w) {}
};

// Hash fonksiyonu
int hashFunction(const string& key, int tableSize) {
    int hashVal = 0;
    for (char ch : key) {
        hashVal = 37 * hashVal + ch;
    }
    return hashVal % tableSize;
}

// HashTable sınıfı
class HashTable {
private:
    vector<list<Node>> theLists; // Liste dizisi
    int tableSize; // Hash table boyutu

public:
    HashTable(int size = 10) : tableSize(size) {
        theLists.resize(tableSize);
    }

    void insert(const string &word, const string &fileName) {
        int hashVal = hashFunction(word, tableSize);
        auto &whichList = theLists[hashVal];

        for (auto &node : whichList) {
            if (node.word == word) {
                node.fileCounts[fileName]++; // Kelime zaten varsa sayısını artır
                return;
            }
        }

        Node newNode(word);
        newNode.fileCounts[fileName] = 1; // Yeni kelime ekle
        whichList.push_back(newNode);
    }

    void printTable() const {
        for (int i = 0; i < tableSize; ++i) {
            cout << "Kova [" << i << "]: ";
            for (const auto &node : theLists[i]) {
                cout << node.word << " {";
                for (const auto &fileCount : node.fileCounts) {
                    cout << fileCount.first << ": " << fileCount.second << ", ";
                }
                cout << "} ";
            }
            cout << endl;
        }
    }
};

int main() {
    HashTable ht(10);

    // Kelimeleri ve dosya isimlerini ekle
    ht.insert("example", "file1.txt");
    ht.insert("test", "file2.txt");
    ht.insert("example", "file2.txt");
    ht.insert("word", "file3.txt");
    ht.insert("test", "file1.txt");

    // Hash table'ı yazdır
    ht.printTable();

    return 0;
}
