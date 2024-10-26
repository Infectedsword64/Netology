#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Adresses {
public:
    Adresses(const std::string& city, const std::string& street, const std::string house, const std::string room) {
        this->city = city; 
        this->street = street;
        this->house = house;
        this->room = room;
    }

    std::string string_to_file() {
        return city + ", " + street + ", " + house + ", " + room + '\n';
    }

    const std::string get_city() {
        return this->city;
    }

    const std::string get_street() {
        return this->street;
    }

    const std::string get_house() {
        return this->house;
    }

    const std::string get_room() {
        return this->room;
    }
private:
    std::string city;
    std::string street;
    std::string house;
    std::string room;
};

void sort(std::vector<Adresses>& adresses) {
    for(int j = 0; j < adresses.size(); j++)
        for (int i = 1; i < adresses.size() - j; i++) {
            if (adresses[i - 1].get_city() < adresses[i].get_city()) {
                Adresses buf(adresses[i].get_city(), adresses[i].get_street(), adresses[i].get_house(), adresses[i].get_room());
                adresses[i] = adresses[i - 1];
                adresses[i - 1] = buf;
            }
        }
}

int main() {

    std::ifstream in("in.txt");
    int N = 0;
    std::vector<Adresses> adresses;

    if (in.is_open()) {
        in >> N;
        for (int i = 0; i < N; i++) {
            std::string adress[4];
            in >> adress[0] >> adress[1] >> adress[2] >> adress[3];
            Adresses new_adress = Adresses(adress[0], adress[1], adress[2], adress[3]);
            adresses.push_back(new_adress);
        }
    }
    in.close();

    sort(adresses);

    std::ofstream out("out.txt");
    if (out.is_open()) {
        out << N << "\n";
        for (int i = N - 1; i >= 0; i--) {
            out << adresses[i].string_to_file();
        }
    }
    out.close();

    return 0;
}