#ifndef RANGETREE1D_H
#define RANGETREE1D_H

#include <vector>
#include <algorithm>
#include <iostream>

// Pojedynczy węzeł drzewa zakresowego 1D
struct RangeTreeNode {
    double key;           // Wartość w węźle
    RangeTreeNode* left;  // Lewe poddrzewo
    RangeTreeNode* right; // Prawe poddrzewo

    RangeTreeNode(double k) : key(k), left(nullptr), right(nullptr) {}
};

// Drzewo zakresowe 1D
class RangeTree1D {
private:
    RangeTreeNode* root;
    std::vector<double> sortedData; // Posortowane dane dla szybkiego zapytania

    // Buduje zrównoważone drzewo BST z posortowanej tablicy
    RangeTreeNode* buildBalancedTree(const std::vector<double>& data, int start, int end) {
        if (start > end) return nullptr;

        int mid = start + (end - start) / 2;
        RangeTreeNode* node = new RangeTreeNode(data[mid]);

        node->left = buildBalancedTree(data, start, mid - 1);
        node->right = buildBalancedTree(data, mid + 1, end);

        return node;
    }

    // Optymalny algorytm wyszukiwania przedziału w drzewie 1D
    // Złożoność: O(log n + k) gdzie k = liczba wyników
    void rangeQueryOptimized(RangeTreeNode* node, double minVal, double maxVal, std::vector<double>& result) {
        if (node == nullptr) return;

        // Znajdź węzeł graniczny (split node) - najgłębszy węzeł leżący na ścieżce
        // do obu granic zakresu. To pozwala uniknąć zbędnych odwiedzin.
        if (node->key < minVal) {
            // Całe lewe poddrzewo jest poniżej zakresu - przeszukuj tylko prawo
            rangeQueryOptimized(node->right, minVal, maxVal, result);
            return;
        }
        if (node->key > maxVal) {
            // Całe prawe poddrzewo jest powyżej zakresu - przeszukuj tylko lewo
            rangeQueryOptimized(node->left, minVal, maxVal, result);
            return;
        }

        // Węzeł w zakresie [minVal, maxVal] - dodaj go
        result.push_back(node->key);

        // Optymalizacja: odwiedzaj tylko te poddrzewa, które mogą zawierać
        // wartości z zakresu
        rangeQueryOptimized(node->left, minVal, maxVal, result);
        rangeQueryOptimized(node->right, minVal, maxVal, result);
    }

    // Znajdź węzeł graniczny (split node) dla zakresu [minVal, maxVal]
    // Jest to najgłębszy węzeł, którego klucz leży wewnątrz zakresu
    // lub ostatni wspólny przodek ścieżek do minVal i maxVal
    RangeTreeNode* findSplitNode(RangeTreeNode* node, double minVal, double maxVal) {
        if (node == nullptr) return nullptr;

        if (node->key < minVal) {
            return findSplitNode(node->right, minVal, maxVal);
        }
        if (node->key > maxVal) {
            return findSplitNode(node->left, minVal, maxVal);
        }

        // minVal <= node->key <= maxVal - to jest węzeł graniczny
        return node;
    }

    // Zbierz wszystkie wartości w poddrzewie (dla liści na ścieżce)
    void collectSubtree(RangeTreeNode* node, std::vector<double>& result) {
        if (node == nullptr) return;
        result.push_back(node->key);
        collectSubtree(node->left, result);
        collectSubtree(node->right, result);
    }

    // Klasyczny algorytm wyszukiwania przedziału z użyciem split node
    // Bardziej wydajny dla rzadkich zapytań w dużym drzewie
    void rangeQueryClassic(RangeTreeNode* node, double minVal, double maxVal, std::vector<double>& result) {
        RangeTreeNode* split = findSplitNode(node, minVal, maxVal);
        if (split == nullptr) return;

        // Jeśli split node jest w zakresie, dodaj go
        if (split->key >= minVal && split->key <= maxVal) {
            result.push_back(split->key);
        }

        // Ścieżka od split do minVal - zbieraj prawe poddrzewa
        RangeTreeNode* v = split->left;
        while (v != nullptr) {
            if (v->key >= minVal) {
                // Prawe poddrzewo jest w całości w zakresie
                collectSubtree(v->right, result);
                result.push_back(v->key);
                v = v->left;
            } else {
                v = v->right;
            }
        }

        // Ścieżka od split do maxVal - zbieraj lewe poddrzewa
        v = split->right;
        while (v != nullptr) {
            if (v->key <= maxVal) {
                // Lewe poddrzewo jest w całości w zakresie
                collectSubtree(v->left, result);
                result.push_back(v->key);
                v = v->right;
            } else {
                v = v->left;
            }
        }
    }

    // Usuwa drzewo
    void destroyTree(RangeTreeNode* node) {
        if (node == nullptr) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    RangeTree1D() : root(nullptr) {}

    ~RangeTree1D() {
        destroyTree(root);
    }

    // Buduje drzewo z wektora danych
    void build(const std::vector<double>& data) {
        if (data.empty()) return;

        // Kopiujemy i sortujemy dane
        sortedData = data;
        std::sort(sortedData.begin(), sortedData.end());

        // Budujemy zrównoważone drzewo
        root = buildBalancedTree(sortedData, 0, sortedData.size() - 1);
    }

    // Znajduje wszystkie wartości w zakresie [minVal, maxVal]
    std::vector<double> query(double minVal, double maxVal) {
        std::vector<double> result;

        // Szybsze zapytanie z użyciem posortowanych danych
        auto itStart = std::lower_bound(sortedData.begin(), sortedData.end(), minVal);
        auto itEnd = std::upper_bound(sortedData.begin(), sortedData.end(), maxVal);

        for (auto it = itStart; it != itEnd; ++it) {
            result.push_back(*it);
        }

        return result;
    }

    // Zapytanie z użyciem drzewa - wersja zoptymalizowana
    std::vector<double> queryWithTree(double minVal, double maxVal) {
        std::vector<double> result;
        rangeQueryOptimized(root, minVal, maxVal, result);
        std::sort(result.begin(), result.end());
        return result;
    }

    // Zapytanie z użyciem klasycznego algorytmu ze split node
    std::vector<double> queryClassic(double minVal, double maxVal) {
        std::vector<double> result;
        rangeQueryClassic(root, minVal, maxVal, result);
        std::sort(result.begin(), result.end());
        return result;
    }

    // Wypisuje drzewo (do celów debugowania)
    void printTree(RangeTreeNode* node, int level = 0) {
        if (node == nullptr) return;

        printTree(node->right, level + 1);
        for (int i = 0; i < level; i++) std::cout << "  ";
        std::cout << node->key << std::endl;
        printTree(node->left, level + 1);
    }

    void print() {
        std::cout << "=== Drzewo Zakresowe 1D ===" << std::endl;
        printTree(root);
        std::cout << "===========================" << std::endl;
    }

    int getSize() const {
        return sortedData.size();
    }

    RangeTreeNode* getRoot() {
        return root;
    }
};

#endif
