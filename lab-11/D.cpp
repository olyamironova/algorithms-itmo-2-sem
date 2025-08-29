#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <stack>

int n;
bool best_people_prefers_this_kitty_to_temp_kitty(std::vector<int>& preferences, int this_kitty, int temp_kitty) {
    for (int i = 0; i < n; ++i) {
        if (preferences[i] == this_kitty) {
            return true;
        }
        if (preferences[i] == temp_kitty) {
            return false;
        }
    }
    return false;
}

int main() {
    std::cin >> n;
    std::stack<std::pair<int, int>> free_kitties;
    std::vector<std::vector<int>> preferences_of_kitties(n, std::vector<int>(n));
    std::vector<std::vector<int>> preferences_of_peoples(n, std::vector<int>(n));
    std::map<int, int> proposal_for_kitties;
    std::map<int, int> proposal_for_peoples;
    std::vector<int> ans(n, -1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> preferences_of_kitties[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> preferences_of_peoples[i][j];
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        free_kitties.emplace(std::make_pair(i, 0));
    }
    while (!free_kitties.empty()) {
        auto [free_kitty, i] = free_kitties.top();
        free_kitties.pop();
        int best_people = preferences_of_kitties[free_kitty][i];
        if (!proposal_for_peoples.contains(best_people)) {
            ans[free_kitty] = best_people;
            proposal_for_peoples[best_people] = free_kitty;
            continue;
            // proposal_for_kitties[free_kitty] = best_people;
        } else if (best_people_prefers_this_kitty_to_temp_kitty(preferences_of_peoples[best_people], free_kitty, proposal_for_peoples[best_people])) {
            int prev_kitty = proposal_for_peoples[best_people];
            ans[prev_kitty] = -1;
            ans[free_kitty] = best_people;
            proposal_for_peoples[best_people] = free_kitty;
            free_kitties.emplace(std::make_pair(prev_kitty, 0));
            continue;
        } else {
        }
        free_kitties.emplace(std::make_pair(free_kitty, ++i));
    }
    for (int i = 0; i < n; ++i) {
        std::cout << i << " " << ans[i] << "\n";
    }
}