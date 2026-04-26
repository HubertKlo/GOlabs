#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>
#include <iomanip>
#include "scrp/headers/RangeTree1D.h"

// Wizualizacja punktów 1D na osi liczbowej
void Visualize1DPoints(const std::vector<double>& data, const std::vector<double>& highlight, double minVal, double maxVal) {
    std::cout << "\n=== Wizualizacja na osi liczbowej (0-100) ===" << std::endl;

    // Stwórz histogram
    std::string axis(100, '-');

    // Zaznacz wszystkie punkty
    for (double v : data) {
        int pos = (int)v;
        if (pos >= 0 && pos < 100) {
            axis[pos] = '*';
        }
    }

    // Zaznacz zakres
    for (int i = (int)minVal; i <= (int)maxVal && i < 100; i++) {
        if (i >= 0) axis[i] = (axis[i] == '*') ? '#' : '|';
    }

    std::cout << "0---------1---------2---------3---------4---------5---------6---------7---------8---------9--------->" << std::endl;
    std::cout << axis << std::endl;
    std::cout << "Legenda: * = punkt, | = w zakresie (pusty), # = punkt w zakresie" << std::endl;
}

// Wizualizacja drzewa w formie ASCII
void VisualizeTreeASCII(RangeTreeNode* node, int level, std::string& output) {
    if (node == nullptr) return;

    VisualizeTreeASCII(node->right, level + 1, output);

    for (int i = 0; i < level; i++) output += "    ";
    output += std::to_string((int)node->key) + "\n";

    VisualizeTreeASCII(node->left, level + 1, output);
}

// Test i wizualizacja wyników dla drzewa 1D
void RangeTree1DDemo() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "=== DRZEWO ZAKRESOWE 1D - TESTY I WIZUALIZACJA ===" << std::endl;
    std::cout << std::string(70, '=') << std::endl;

    // Wczytaj dane z pliku
    std::ifstream file("data_1d.txt");
    if (!file.is_open()) {
        std::cerr << "Nie mozna otworzyc pliku data_1d.txt" << std::endl;
        return;
    }

    std::vector<double> data;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        data.push_back(std::stod(line));
    }
    file.close();

    std::cout << "\nWczytano " << data.size() << " punktow 1D" << std::endl;

    // Zbuduj drzewo
    RangeTree1D tree;
    tree.build(data);

    // Wizualizacja drzewa
    std::cout << "\n=== STRUKTURA DRZEWA (odwrócone - prawo u góry) ===" << std::endl;
    std::string treeViz;
    VisualizeTreeASCII(tree.getRoot(), 0, treeViz);
    std::cout << treeViz << std::endl;

    // Wizualizacja na osi liczbowej
    Visualize1DPoints(data, {}, 0, 100);

    // Testowe zapytania z wizualizacją
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "=== TESTOWE ZAPYTANIA ZAKRESOWE ===" << std::endl;
    std::cout << std::string(70, '=') << std::endl;

    std::vector<std::pair<double, double>> queries = {
        {10, 30},
        {50, 70},
        {80, 100},
        {0, 15},
        {20, 60}
    };

    for (size_t i = 0; i < queries.size(); i++) {
        double minVal = queries[i].first;
        double maxVal = queries[i].second;

        std::cout << "\n[Zapytanie " << (i + 1) << "] Zakres: [" << minVal << ", " << maxVal << "]" << std::endl;
        std::cout << std::string(50, '-') << std::endl;

        auto start = std::chrono::high_resolution_clock::now();
        std::vector<double> result = tree.query(minVal, maxVal);
        auto end = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        std::cout << "Czas: " << time << " µs" << std::endl;
        std::cout << "Liczba wyników: " << result.size() << std::endl;
        std::cout << "Wyniki: ";
        for (double v : result) {
            std::cout << (int)v << " ";
        }
        std::cout << std::endl;

        // Wizualizacja tego zapytania
        Visualize1DPoints(data, result, minVal, maxVal);
    }

    // Szczegółowe testy wydajności
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "=== TEST WYDAJNOSCI - ZALEZNOSC OD n ===" << std::endl;
    std::cout << std::string(70, '=') << std::endl;

    std::vector<int> sizes = {100, 500, 1000, 2000, 5000, 10000};
    std::vector<long long> buildTimes, queryTimes;

    std::cout << "\n" << std::setw(10) << "n"
              << std::setw(15) << "Budowanie [µs]"
              << std::setw(15) << "Zapytanie [µs]"
              << std::setw(10) << "k" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    for (int n : sizes) {
        std::vector<double> testData;
        for (int i = 0; i < n; i++) {
            testData.push_back(rand() % 100000);
        }

        RangeTree1D testTree;

        auto buildStart = std::chrono::high_resolution_clock::now();
        testTree.build(testData);
        auto buildEnd = std::chrono::high_resolution_clock::now();
        long long buildTime = std::chrono::duration_cast<std::chrono::microseconds>(buildEnd - buildStart).count();
        buildTimes.push_back(buildTime);

        auto queryStart = std::chrono::high_resolution_clock::now();
        auto r = testTree.query(25000, 75000);
        auto queryEnd = std::chrono::high_resolution_clock::now();
        long long queryTime = std::chrono::duration_cast<std::chrono::microseconds>(queryEnd - queryStart).count();
        queryTimes.push_back(queryTime);

        std::cout << std::setw(10) << n
                  << std::setw(15) << buildTime
                  << std::setw(15) << queryTime
                  << std::setw(10) << r.size() << std::endl;
    }

    // Wykres słupkowy (ASCII) dla czasu budowania
    std::cout << "\n=== Wykres czasu budowania ===" << std::endl;
    long long maxBuild = *std::max_element(buildTimes.begin(), buildTimes.end());
    for (size_t i = 0; i < sizes.size(); i++) {
        int barLen = (buildTimes[i] * 40) / maxBuild;
        std::cout << std::setw(6) << sizes[i] << " |";
        for (int j = 0; j < barLen; j++) std::cout << "#";
        std::cout << " " << buildTimes[i] << " µs" << std::endl;
    }

    // Wykres dla czasu zapytania
    std::cout << "\n=== Wykres czasu zapytania ===" << std::endl;
    long long maxQuery = *std::max_element(queryTimes.begin(), queryTimes.end());
    for (size_t i = 0; i < sizes.size(); i++) {
        int barLen = (maxQuery > 0) ? (queryTimes[i] * 40) / maxQuery : 0;
        std::cout << std::setw(6) << sizes[i] << " |";
        for (int j = 0; j < barLen; j++) std::cout << "#";
        std::cout << " " << queryTimes[i] << " µs" << std::endl;
    }

    // Porównanie trzech metod
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "=== PORÓWNANIE METOD ZAPYTAŃ ===" << std::endl;
    std::cout << std::string(70, '=') << std::endl;

    std::vector<double> largeData;
    for (int i = 0; i < 10000; i++) {
        largeData.push_back(rand() % 100000);
    }

    RangeTree1D largeTree;
    largeTree.build(largeData);

    std::cout << "\nn = 10000 elementów:" << std::endl;

    std::vector<std::pair<double, double>> testQueries = {
        {0, 1000},      // wąski zakres
        {0, 50000},     // średni zakres
        {0, 100000}     // szeroki zakres
    };

    std::cout << "\n" << std::setw(15) << "Zakres"
              << std::setw(20) << "Tablica [µs]"
              << std::setw(20) << "Drzewo (opt) [µs]"
              << std::setw(20) << "Drzewo (klas) [µs]" << std::endl;
    std::cout << std::string(75, '-') << std::endl;

    for (const auto& q : testQueries) {
        std::ostringstream oss;
        oss << "[" << q.first << ", " << q.second << "]";

        auto t1 = std::chrono::high_resolution_clock::now();
        auto r1 = largeTree.query(q.first, q.second);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto time1 = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

        auto t3 = std::chrono::high_resolution_clock::now();
        auto r2 = largeTree.queryWithTree(q.first, q.second);
        auto t4 = std::chrono::high_resolution_clock::now();
        auto time2 = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();

        auto t5 = std::chrono::high_resolution_clock::now();
        auto r3 = largeTree.queryClassic(q.first, q.second);
        auto t6 = std::chrono::high_resolution_clock::now();
        auto time3 = std::chrono::duration_cast<std::chrono::microseconds>(t6 - t5).count();

        std::cout << std::setw(15) << oss.str()
                  << std::setw(20) << time1
                  << std::setw(20) << time2
                  << std::setw(20) << time3 << std::endl;
    }

    // Wizualizacja zależności czasu od k (liczby wyników)
    std::cout << "\n=== Zależność czasu od k (liczby wyników) ===" << std::endl;
    std::cout << std::setw(10) << "k" << std::setw(15) << "Czas [µs]" << std::setw(20) << "Wykres" << std::endl;
    std::cout << std::string(45, '-') << std::endl;

    std::vector<std::pair<double, double>> kQueries = {
        {0, 100}, {0, 500}, {0, 1000}, {0, 5000},
        {0, 10000}, {0, 25000}, {0, 50000}, {0, 75000}, {0, 100000}
    };

    std::vector<int> kValues;
    std::vector<long long> kTimes;

    for (const auto& q : kQueries) {
        auto t1 = std::chrono::high_resolution_clock::now();
        auto r = largeTree.query(q.first, q.second);
        auto t2 = std::chrono::high_resolution_clock::now();
        long long time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

        kValues.push_back(r.size());
        kTimes.push_back(time);
    }

    long long maxKTime = *std::max_element(kTimes.begin(), kTimes.end());
    for (size_t i = 0; i < kValues.size(); i++) {
        int barLen = (kTimes[i] * 30) / (maxKTime > 0 ? maxKTime : 1);
        std::cout << std::setw(10) << kValues[i]
                  << std::setw(15) << kTimes[i]
                  << " |";
        for (int j = 0; j < barLen; j++) std::cout << "#";
        std::cout << std::endl;
    }

    // Podsumowanie
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "=== PODSUMOWANIE ===" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    std::cout << "Złożoność budowania:  O(n log n)" << std::endl;
    std::cout << "Złożoność zapytania:  O(log n + k) - OPTYMALNE" << std::endl;
    std::cout << "Złożoność pamięci:    O(n)" << std::endl;
    std::cout << "Dolne ograniczenie:   Ω(log n + k) - OSIĄGNIĘTE" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
}

int main() {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "TEST DRZEWA ZAKRESOWEGO 1D" << std::endl;
    std::cout << std::string(70, '=') << std::endl;

    RangeTree1DDemo();

    return 0;
}
