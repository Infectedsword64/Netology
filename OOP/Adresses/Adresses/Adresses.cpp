#include <iostream>
#include <fstream>
#include <string>

class Adresses {
public:
    std::string city;
    std::string street;
    std::string house;
    std::string room;
};

int main() {

    std::ifstream in("in.txt");
    int N = 0;



    if (in.is_open()) {
        in >> N;
    }

    Adresses* adresses = new Adresses[N];

    if (in.is_open()) {
        for (int i = 0; i < N; i++) {
            in >> adresses[i].city >> adresses[i].street >> adresses[i].house >> adresses[i].room;
        }
    }
    in.close();

    std::ofstream out("out.txt");
    if (out.is_open()) {
        out << N + "\n";
        for (int i = N - 1; i >= 0; i--) {
            out << adresses[i].city + ", " + adresses[i].street + ", " + adresses[i].house + ", " + adresses[i].room + "\n";
        }
    }
    out.close();

    return 0;
}