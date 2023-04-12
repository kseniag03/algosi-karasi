/*
1) АиСД-2, 2023, задание 2
2) Ганина Ксения Андреевна 212
3) CLion
4) генерация текста, 3 алгоритма на поиск, учёт подстановок '?' в искомый паттерн, графики, выводы
5) усреднение результатов, ???
*/

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "find_string_pattern.h"

int64_t timespecDifference(struct timespec a, struct timespec b) {
    int64_t timeA, timeB;
    timeA = a.tv_sec;
    timeA *= 1000000000;
    timeA += a.tv_nsec;
    timeB = b.tv_sec;
    timeB *= 1000000000;
    timeB += b.tv_nsec;
    return timeA - timeB;
}

const char alphabet[] = { 'a', 'b', 'c', 'd' };

const int size1 = 10000;

const int size2 = 100000;

// get text for current parameters
std::string getText(int alp, int size, std::string &s) {
    auto alphabet_size = (alp) ? 4 : 2;
    auto count = (size) ? size2 : size1;
    int j = 0;
    while (s.size() < count) {
        int i = rand() % alphabet_size;
        s.insert(j++, &alphabet[i], 1);
    }
    return s;
}

// get texts to work with
std::vector< std::vector< std::vector< std::vector<std::string> > > > getStringData() {
    std::vector< std::vector< std::vector< std::vector<std::string> > > > v (
            2, std::vector< std::vector< std::vector<std::string> > > (
                    2, std::vector< std::vector<std::string> > (
                            5, std::vector<std::string> (
                                    1, ""
                            )
                    )
            )
    );
    for (int alp = 0; alp < 2; ++alp) {
        for (int size = 0; size < 2; ++size) {
            for (int wildcard = 0; wildcard < 5; ++wildcard) {
                for (int i = 0; i < 1; ++i) {
                    v[alp][size][wildcard][i] = getText(alp, size, v[alp][size][wildcard][i]);
                }
            }
        }
    }
    return v;
}

// add wildcards to random places in pattern
void editPattern(std::string &pattern, int wildcard) {
    std::set<int> pos;
    while (pos.size() < wildcard) {
        int p = rand() % pattern.size();
        pos.insert(p);
    }
    for (auto p : pos) {
        pattern[p] = '?';
    }
}

// get pattern and measure time for 3 algo
//                                             text   pattern cnt  time
void fillTime(std::vector< std::pair< std::pair<std::string, int>, std::vector<int64_t> > > &v, int i,
              bool alp, int wildcard) {
    auto pair = v[i].first;
    auto text = pair.first;
    int count = pair.second;

    if (wildcard > count) {
        wildcard = count;
    }

    int start_position = rand() % (text.size() - count);
    std::string pattern = text.substr(start_position, count);
    editPattern(pattern, wildcard);

    //   std::cout << "pattern: " << pattern << /*" from str: " << text << " count: " << count << */"\n";

    auto f = new FindStringPattern(text, pattern, alp);

    struct timespec start = {}, end = {};

    int64_t elapsed_ns;
    clock_gettime(CLOCK_MONOTONIC, &start);
    f->naive();
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_ns = timespecDifference(end, start);
    v[i].second.push_back(elapsed_ns);

    clock_gettime(CLOCK_MONOTONIC, &start);
    f->brKMP();
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_ns = timespecDifference(end, start);
    v[i].second.push_back(elapsed_ns);

    clock_gettime(CLOCK_MONOTONIC, &start);
    f->brsKMP();
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_ns = timespecDifference(end, start);
    v[i].second.push_back(elapsed_ns);
}

// output to console
void outputTime(std::vector< std::pair< std::pair<std::string, int>, std::vector<int64_t> > > &v) {
    for (int i = 0; i < v.size(); ++i) {
        for (auto &x : v[i].second) {
            std::cout << x << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n\n";
}

// output to txt file:
// 1st column -- naive, 2nd -- kmp with br, 3rd -- kmp with brs
void outputFile(const std::vector< std::pair< std::pair<std::string, int>, std::vector<int64_t> > > &v, const std::string& filename) {
    std::ofstream outfile(filename, std::ios_base::app);
    if (outfile.is_open()) {
        for (int i = 0; i < v.size(); ++i) {
            for (auto &x : v[i].second) {
                outfile << x << " ";
            }
            outfile << "\n";
        }
        outfile << "\n\n";
        outfile.close();
    }
}

// main
int main() {

    srand(time(nullptr));
    auto data = getStringData();

    for (int alp = 0; alp < 2; ++alp) {
        for (int size = 0; size < 2; ++size) {
            for (int wildcard = 0; wildcard < 5; ++wildcard) {

                std::vector< std::pair< std::pair<std::string, int>, std::vector<int64_t> > > v;
                auto str = data[alp][size][wildcard][0];
                for (int i = 100; i <= 3000; i += 100) {
                    auto pair = std::make_pair(str, i);
                    std::vector<int64_t> empty_vec;
                    auto makePair = std::make_pair(pair, empty_vec);
                    v.push_back(makePair);
                    fillTime(v, v.size() - 1, alp, wildcard);
                }

                //outputTime(v);

                std::vector<std::string> names;
                names.push_back(alp ? "4-alp" : "2-alp");
                names.push_back(size ? "1e6" : "1e5");
                names.push_back(wildcard ? "with-" : "without");
                names.push_back(wildcard ? std::to_string(wildcard) + "-replace" : "");

                auto fileName = names[0];
                for (int i = 1; i < names.size(); ++i) {
                    if (i < names.size() - 1) {
                        fileName += "_";
                    }
                    fileName += names[i];
                }
                fileName += ".txt";
                std::cout << fileName << "\n";

                std::ofstream datafile(fileName, std::ios_base::trunc);
                datafile.close();

                //outputFile(v, fileName); // comment for not making new files


            }
        }
    }

    return 0;
}
