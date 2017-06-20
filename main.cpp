//
//  main.cpp
//  advanced-extend-to-palindrome
//
//  Created by olderor on 20.06.17.
//  Copyright © 2017 Bohdan Yevchenko. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>

std::vector<int> prefix_func;
std::string str;
int str_len;

int best_prefix_func_index = 0;

void calc_prefix_function() {
    best_prefix_func_index = 0;
    prefix_func.resize(str_len);
    prefix_func[0] = 0;

    int matched_prefix, candidate;
    for (int current = 1; current < str.size(); ++current) {
        matched_prefix = current - 1;
        candidate = prefix_func[matched_prefix];
        while (candidate != 0 &&
          str[str_len - current - 1] != str[str_len - candidate - 1]) {
            matched_prefix = prefix_func[matched_prefix] - 1;
            candidate = prefix_func[matched_prefix];
        }

        if (candidate == 0) {
            prefix_func[current] =
              str[str_len - current - 1] == str[str_len - 1];
        } else {
            prefix_func[current] = candidate + 1;
        }
    }
}

int main() {
    while (std::cin >> str) {
        str_len = static_cast<int>(str.length());
        calc_prefix_function();

        int candidate = 0;

        for (int i = 0; i < str_len; ++i) {
            while (candidate != 0 && str[i] != str[str_len - candidate - 1]) {
                candidate = prefix_func[candidate - 1];
            }

            if (str[i] == str[str_len - candidate - 1]) {
                ++candidate;
            }

            if (i != str_len - 1 && candidate == str_len) {
                candidate = prefix_func[str_len - 1];
            }
        }

        std::cout << str;
        for (int i = str_len - candidate - 1; i >= 0; --i) {
            std::cout << str[i];
        }
        std::cout << "\n";
    }
    return 0;
}
