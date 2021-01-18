#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std::chrono;
using namespace std;

void read_input(string file_name)
{
    ifstream ifs;

    ifs.open(file_name.c_str(), ios::in);
    if (!ifs.is_open()) {
        cout << "Error: cannot open input_file: " << file_name << "\n";
        exit(1);
    }

    ifs.close();
}

void solve()
{
}

void write_output(string output_file)
{
    ofstream ofs;

    ofs.open(output_file.c_str(), ios::out);
    if (!ofs.is_open()) {
        cout << "Error: cannot open output_file: " << output_file << "\n";
        exit(1);
    }

    ofs.close();
}

int main(int argc, char *argv[])
{
    vector<string> input_files;

    for (unsigned int i = 1; i < argc; i++) {
        input_files.push_back(argv[i]);
    }

    for (unsigned int i = 0; i < input_files.size(); i++) {
        auto start = high_resolution_clock::now();
        read_input("input/" + input_files[i]);
        solve();
        write_output("output/" + input_files[i]);
        auto end = high_resolution_clock::now();
        auto dur = duration_cast<seconds>(end - start);
        cout << "Running time: " << dur.count() << "\n";
    }

    return 0;
}
