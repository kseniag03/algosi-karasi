#include <utility>
#include <vector>
#include <string>
#include <iostream>

class FindStringPattern {
public:

    void generate_strings(std::string str, int pos, bool alp) {
        if (pos == str.length()) {
            //std::cout << str << "\n";
            patterns_.push_back(str);
            return;
        }
        if (str[pos] == '?') {
            for (char c = 'a'; c <= (alp ? 'd' : 'b'); c++) {
                str[pos] = c;
                generate_strings(str, pos + 1, alp);
                str[pos] = '?';
            }
        } else {
            generate_strings(str, pos + 1, alp);
        }
    }

    FindStringPattern() {
        patterns_.clear();
    }

    FindStringPattern(std::string &text, std::string &pattern, bool alp) : t_(text), p_(pattern) {
        patterns_.clear();
        generate_strings(pattern, 0, alp);
    }

    void naive() {
        //std::cout << "Naive\n";
        implementNaiveSearch();
        //std::cout << "\n";
    }

    void brKMP() {
        //std::cout << "KMP with br\n";
        for (auto &p : patterns_) {
            auto s = p + "$" + t_;
            auto br = getBrVec(s);
            implementKnuthMorrisPratt(br, p);
        }
        //std::cout << "\n";
    }

    void brsKMP() {
        //std::cout << "KMP with brs\n";
        for (auto &p : patterns_) {
            auto s = p + "$" + t_;
            auto br = getBrVec(s);
            auto brs = getBrsVec(s, br);
            implementKnuthMorrisPratt(brs, p);
        }
        //std::cout << "\n";
    }

private:
    std::string t_;
    std::string p_;

    std::vector<std::string> patterns_;

    void implementNaiveSearch() {
        int ind = -1;
        for (int i = 0; i < t_.size() - p_.size() + 1; ++i) {
            bool f = true;
            for (int j = 0; j < p_.size(); ++j) {
                if (p_[j] != t_[i + j] && p_[j] != '?') {
                    f = false;
                    break;
                }
            }
            if (f) {
                ind = i;
                //std::cout << ind << " ";
            }
        }
    }

    void implementKnuthMorrisPratt(std::vector<int> &edges, std::string &pattern) {
        int t_ind = 0;
        int p_ind = 0;
        std::vector<int> result;
        while (t_ind < static_cast<int>(t_.size())) {
            if (p_ind < static_cast<int>(pattern.size()) &&
                (t_[t_ind] == pattern[p_ind] || pattern[p_ind] == '?')) {
                t_ind++;
                p_ind++;
                if (p_ind == static_cast<int>(pattern.size())) {
                    result.push_back(t_ind - p_ind);
                }
            } else {
                if (p_ind == 0) {
                    t_ind++;
                } else {
                    p_ind = edges[p_ind - 1];
                }
            }
        }
        /*
        for (auto x : result) {
            std::cout << x << " ";
        }*/
    }

    std::vector<int> getBrVec(std::string &s) {
        int n = static_cast<int>(s.size());
        std::vector<int> br(n);
        for (int i = 1; i < n; ++i) {
            int k = br[i - 1];
            while (k > 0 && (s[i] != s[k] && s[k] != '?')) {
                k = br[k - 1];
            }
            if (s[i] == s[k] || s[k] == '?') {
                ++k;
            }
            while (k < i && s[k] == '?') {
                ++k;
            }
            br[i] = k;
            if (k == i && s[i] == '?') {
                br[i] = k - 1;
            }
        }
        return br;
    }

    std::vector<int> getBrsVec(std::string &s, std::vector<int> &br) {
        int n = static_cast<int>(s.size());
        std::vector<int> brs(n);
        for (int i = 1; i < n; ++i) {
            if (s[br[i] + 1] != s[i]) {
                brs[i] = br[i];
            } else {
                brs[i] = brs[br[i]];
            }
        }
        return brs;
    }

};
