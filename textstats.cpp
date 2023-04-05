#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <cctype>
#include <algorithm>
#include <vector>
#include <limits>

class TextStats {
private:
    std::string fileName;
    int wordCount;
    int lineCount;
    int charCount;
    std::map<std::string, int> wordOccurrences;
    int upperCaseCount;
    int lowerCaseCount;
    int longestWordLength;
    int digitCount;
    std::string longestLine;
    std::map<char, int> letterFrequencies;
    int punctuationCount;

public:
    TextStats(std::string fName)
        : fileName(fName), wordCount(0), lineCount(0), charCount(0), upperCaseCount(0), lowerCaseCount(0),
          longestWordLength(0), digitCount(0), punctuationCount(0) {
        for (char c = 'a'; c <= 'z'; ++c) {
            letterFrequencies[c] = 0;
        }
    }

    void countStats() {
        std::ifstream inputFile(fileName);
        std::string line;
        std::string word;

        if (!inputFile.is_open()) {
            std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
            return;
        }

        while (std::getline(inputFile, line)) {
            std::istringstream lineStream(line);
            lineCount++;
            charCount += line.length();

            if (line.length() > longestLine.length()) {
                longestLine = line;
            }

            for (char c : line) {
                if (std::isupper(c)) {
                    upperCaseCount++;
                    letterFrequencies[std::tolower(c)]++;
                } else if (std::islower(c)) {
                    lowerCaseCount++;
                    letterFrequencies[c]++;
                } else if (std::isdigit(c)) {
                    digitCount++;
                } else if (std::ispunct(c)) {
                    punctuationCount++;
                }
            }

            while (lineStream >> word) {
                wordCount++;
                longestWordLength = std::max(longestWordLength, static_cast<int>(word.length()));
                wordOccurrences[word]++;
            }
        }

        inputFile.close();
    }

    int getWordCount() const {
        return wordCount;
    }

    int getLineCount() const {
        return lineCount;
    }

    int getCharCount() const {
        return charCount;
    }

    const std::map<std::string, int>& getWordOccurrences() const {
        return wordOccurrences;
    }

    int getUpperCaseCount() const {
        return upperCaseCount;
    }

    int getLowerCaseCount() const {
        return lowerCaseCount;
    }

    int getLongestWordLength() const {
        return longestWordLength;
    }

    int getDigitCount() const {
        return digitCount;
    }

    const std::string& getLongestLine() const {
        return longestLine;
    }
};

    const std::map<char, int>& getLetterFrequencies() const {
        return letterFrequencies;
    }

    int getPunctuationCount() const {
        return punctuationCount;
    }
};

bool comparePairs(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    return a.second > b.second;
}

int main() {
    std::string fileName;

    std::cout << "Entrez le nom du fichier texte : ";
    std::cin >> fileName;

    TextStats stats(fileName);
    stats.countStats();

    int choice;

    while (true) {
        std::cout << "\nMenu des options :" << std::endl;
        std::cout << "1. Afficher les statistiques de base" << std::endl;
        std::cout << "2. Afficher les occurrences de chaque mot" << std::endl;
        std::cout << "3. Afficher le nombre de lettres majuscules et minuscules" << std::endl;
        std::cout << "4. Afficher la longueur du mot le plus long" << std::endl;
        std::cout << "5. Afficher le nombre de chiffres" << std::endl;
        std::cout << "6. Rechercher un mot spécifique" << std::endl;
        std::cout << "7. Afficher la ligne la plus longue" << std::endl;
        std::cout << "8. Quitter" << std::endl;
        std::cout << "Entrez votre choix : ";
        std::cin >> choice;
    
        switch (choice) {
        case 1:
            std::cout << "Nombre de mots : " << stats.getWordCount() << std::endl;
            std::cout << "Nombre de lignes : " << stats.getLineCount() << std::endl;
            std::cout << "Nombre de caractères : " << stats.getCharCount() << std::endl;
            break;
        case 2:
            std::cout << "Occurrences de chaque mot :" << std::endl;
            for (const auto &entry : stats.getWordOccurrences()) {
                std::cout << entry.first << ": " << entry.second << std::endl;
            }
            break;
        case 3:
            std::cout << "Nombre de lettres majuscules : " << stats.getUpperCaseCount() << std::endl;
            std::cout << "Nombre de lettres minuscules : " << stats.getLowerCaseCount() << std::endl;
            break;
        case 4:
            std::cout << "Longueur du mot le plus long : " << stats.getLongestWordLength() << std::endl;
            break;
        case 5:
            std::cout << "Nombre de chiffres : " << stats.getDigitCount() << std::endl;
            break;
        case 6:
            {
                std::string searchTerm;
                std::cout << "Entrez le mot à rechercher : ";
                std::cin >> searchTerm;
                auto it = stats.getWordOccurrences().find(searchTerm);
                if (it != stats.getWordOccurrences().end()) {
                    std::cout << "Le mot '" << searchTerm << "' apparaît " << it->second << " fois." << std::endl;
                } else {
                    std::cout << "Le mot '" << searchTerm << "' n'a pas été trouvé." << std::endl;
                }
            }
            break;
        case 7:
            std::cout << "La ligne la plus longue est :" << std::endl;
            std::cout << stats.getLongestLine() << std::endl;
            break;
        case 8:
                std::cout << "Fréquence des lettres :" << std::endl;
                for (const auto &entry : stats.getLetterFrequencies()) {
                    std::cout << entry.first << ": " << entry.second << std::endl;
                }
                break;
            case 9:
            case 10:
                {
                    std::vector<std::pair<std::string, int>> wordFrequencyList(stats.getWordOccurrences().begin(), stats.getWordOccurrences().end());
                    std::sort(wordFrequencyList.begin(), wordFrequencyList.end(), comparePairs);

                    int displayCount;
                    std::cout << "Combien de mots voulez-vous afficher ? ";
                    std::cin >> displayCount;

                    std::cout << (choice == 9 ? "Mots les plus fréquents" : "Mots les moins fréquents") << ":" << std::endl;
                    for (int i = 0; i < displayCount && i < wordFrequencyList.size(); ++i) {
                        const auto &entry = choice == 9 ? wordFrequencyList[i] : wordFrequencyList[wordFrequencyList.size() - 1 - i];
                        std::cout << entry.first << ": " << entry.second << std::endl;
                    }
                }
                break;
            case 11:
                std::cout << "Nombre de signes de ponctuation : " << stats.getPunctuationCount() << std::endl;
                break;
            case 12:
                std::cout << "Au revoir !" << std::endl;
                return 0;
            default:
                std::cout << "Choix invalide. Veuillez réessayer." << std::endl;
        }
    }

    return 0;
}
