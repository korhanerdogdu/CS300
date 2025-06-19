#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Fonksiyon tanımlamaları
std::string cleanWord(const std::string& word);
void countWordOccurrences(const std::string& filename, std::vector<std::pair<std::string, int>>& wordOccurrences);

int main() {
    const std::string filename = "a.txt"; // Dosya adını değiştirin

    // Vektörü oluştur
    std::vector<std::pair<std::string, int>> wordOccurrences;

    // Dosyadan kelime sayılarını al
    countWordOccurrences(filename, wordOccurrences);

    // Vektördeki değerlere erişerek ekrana yazdır
    for (size_t i = 0; i < wordOccurrences.size(); ++i) {
        std::cout << "Index " << i << ": " << wordOccurrences[i].first << ": " << wordOccurrences[i].second << std::endl;
    }

    return 0;
}

// Kelimeyi temizleme (noktalama işaretlerini ve büyük harfleri temizleme)
std::string cleanWord(const std::string& word) {
    std::string cleanedWord = word;
    // Noktalama işaretlerini temizleme
    cleanedWord.erase(std::remove_if(cleanedWord.begin(), cleanedWord.end(), ::ispunct), cleanedWord.end());
    // Büyük harfleri küçük harfe çevirme
    std::transform(cleanedWord.begin(), cleanedWord.end(), cleanedWord.begin(), ::tolower);
    return cleanedWord;
}

// Kelime sayılarını vektöre ekleme
void countWordOccurrences(const std::string& filename, std::vector<std::pair<std::string, int>>& wordOccurrences) { // 3. parametre pair türüdür. . Bu tür, iki farklı veri tipini bir arada tutmak için kullanılır. İlk veri tipi std::string, ikinci veri tipi ise int'dir. Yani, bu yapı bir kelimenin kendisini (std::string) ve bu kelimenin sayısını (int) bir arada tutar.
    
    
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Dosya acilamadi: " << filename << std::endl;
        return;
    }

    std::string word;

    while (file >> word) {
        word = cleanWord(word);
        
        // Kelime zaten vektörde var mı kontrol et
        auto it = std::find_if(wordOccurrences.begin(), wordOccurrences.end(),
                               [word](const std::pair<std::string, int>& info) { return info.first == word; });

        if (it != wordOccurrences.end()) {
            // Kelime vektörde varsa sayısını artır
            it->second++;
        } else {
            // Kelime vektörde yoksa ekleyin
            wordOccurrences.push_back({word, 1});
        }
    }

    
    
    
    // Dosyayı kapatma
    file.close();
}

