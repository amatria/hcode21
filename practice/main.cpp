#include <algorithm>
#include <unordered_map>
#include <set>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <map>

using namespace std::chrono;
using namespace std;

struct pizza {
    unsigned int id;
    unsigned int num_ingredients;
    vector<int> ingredients;
};

struct delivery {
    unsigned int score;
    unsigned int team_size;
    vector<pizza> pizzas;
    set<int> _ingredients;

    void add_pizza(pizza a) {
        pizzas.push_back(a);

        // only add to score after comparing with second
        if (pizzas.size() == 1)
            score = 0;

        for (int ingredient : a.ingredients) {
            // ingredient not present
            // with C++20 we could use contains
            if (_ingredients.find(ingredient) == _ingredients.end()) {
                _ingredients.insert(ingredient);
                score++;
            }
        }
    }

    unsigned int possible_score(pizza a) {
        unsigned int tmp_score = score;

        for (int ingredient : a.ingredients) {
             // with C++20 we could use contains
            if (_ingredients.find(ingredient) == _ingredients.end())
                ++tmp_score;
        }

        return tmp_score;
    }
};

unsigned int M;
unsigned int T2;
unsigned int T3;
unsigned int T4;
vector<pizza> pizzas;
vector<delivery> deliveries;

unordered_map<string, int> ingredients;
int total_ingredients = 0;
unsigned int final_score = 0;

unsigned int sort_pizzas(pizza &a, pizza &b) {
    return a.ingredients.size() > b.ingredients.size();
}

void read_input(string file_name) {
    ifstream ifs;

    ifs.open(file_name.c_str(), ios::in);
    ifs >> M >> T2 >> T3 >> T4;

    pizzas.clear();
    for (unsigned int i = 0; i < M; i++) {
        unsigned int num_ingredients;
        string ingredientName;
        int ingredient;
        pizza p;

        ifs >> num_ingredients;
        for (unsigned int j = 0; j < num_ingredients; j++) {
            ifs >> ingredientName;
            if (ingredients.count(ingredientName) == 0)
                ingredients[ingredientName] = total_ingredients++;
            p.ingredients.push_back(ingredients[ingredientName]);
        }
        p.num_ingredients = num_ingredients;
        p.id = i;

        pizzas.push_back(p);
    }

    ifs.close();
}

unsigned int get_biggest_team_size() {
    unsigned int team_size = 0;

    if (T4 > 0) {
        team_size = 4;
        T4--;
    } else if (T3 > 0) {
        team_size = 3;
        T3--;
    } else if (T2 > 0) {
        team_size = 2;
        T2--;
    }

    if (pizzas.size() < team_size)
        team_size = 0;

    return team_size;
}

void solve() {
    unsigned int max_idx;
    unsigned int tmp_score;
    unsigned int max_score;
    unsigned int team_size;
    pizza a, b;
    delivery d;

    deliveries.clear();
    sort(pizzas.begin(), pizzas.end(), sort_pizzas);
    while (true) {
        team_size = get_biggest_team_size();

        if (!team_size) {
            break;
        }

        d.score = 0;
        d.team_size = team_size;
        d.pizzas.clear();
        d._ingredients.clear();

        // Always allocate the biggest pizza
        d.add_pizza(pizzas[0]);
        pizzas.erase(pizzas.begin());

        // Greedy allocation for bigger than 2 teams
        for (unsigned int i = 1; i < team_size; i++) {
            b = pizzas[0];
            max_idx = 0;
            max_score = d.possible_score(b);

            for (unsigned int j = 1; j < pizzas.size(); j++) {
                a = pizzas[j];

                if (d.score + a.ingredients.size() < max_score) {
                    break;
                }

                tmp_score = d.possible_score(a);

                if (tmp_score > max_score
                        || (tmp_score == max_score
                            && a.ingredients.size() < b.ingredients.size())) {
                    b = a;
                    max_idx = j;
                    max_score = tmp_score;
                }
            }

            d.add_pizza(b);
            pizzas.erase(pizzas.begin() + max_idx);
        }
        deliveries.push_back(d); 
    }
}

void write_output(string output_file) {
    unsigned int total_score = 0;
    ofstream ofs;

    ofs.open(output_file.c_str(), ios::out);
    ofs << deliveries.size() << "\n";

    for (delivery d : deliveries) {
        total_score += d.score * d.score;
        ofs << d.team_size;

        for (pizza p : d.pizzas) {
            ofs << " " << p.id;
        }
        ofs << "\n";
    }

    cout << "Total score: " << total_score << "\n";
    final_score += total_score;
    ofs.close();
}

int main(int argc, char *argv[]) {
    vector<string> input_files;

    for (unsigned int i = 1; i < argc; i++) {
        input_files.push_back(argv[i]);
    }

    for (auto input_file : input_files) {
        auto start = high_resolution_clock::now();
        read_input("input/" + input_file);
        solve();
        write_output("output/" + input_file);
        auto end = high_resolution_clock::now();
        auto dur = duration_cast<seconds>(end - start);
        cout << "Running time: " << dur.count() << "\n";
    }
    cout << "Total score: " << final_score << "\n";

    return 0;
}
