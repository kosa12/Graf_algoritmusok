// Kosa Matyas, 512, kmim2252
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
// #include <chrono>

using namespace std;
// using namespace chrono;

struct City
{
    int id;
    double x;
    double y;
};

double distance(const City &a, const City &b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

vector<City> read_cities_from_file(const string &filename)
{
    vector<City> cities;
    ifstream file(filename);

    City city;
    while (file >> city.id >> city.x >> city.y)
    {
        cities.push_back(city);
    }

    return cities;
}

void two_opt(vector<City> &route, double &total_distance)
{
    int num_cities = route.size();
    bool improvement = true;

    while (improvement)
    {
        improvement = false;

        for (int i = 1; i < num_cities - 1; ++i)
        {
            for (int j = i + 1; j < num_cities; ++j)
            {
                double old_distance = distance(route[i - 1], route[i]) + distance(route[j - 1], route[j]);
                double new_distance = distance(route[i - 1], route[j - 1]) + distance(route[i], route[j]);

                if (new_distance < old_distance)
                {
                    reverse(route.begin() + i, route.begin() + j);
                    total_distance -= (old_distance - new_distance);
                    improvement = true;
                }
            }
        }
    }
}

int main()
{
    string input_file = "be.txt";
    vector<City> cities = read_cities_from_file(input_file);
    ofstream output_file("ki.txt");

    double total_distance = 0;
    for (int i = 0; i < cities.size() - 1; ++i)
    {
        total_distance += distance(cities[i], cities[i + 1]);
    }
    total_distance += distance(cities.back(), cities.front());

    // auto start = high_resolution_clock::now();
    two_opt(cities, total_distance);
    // auto stop = high_resolution_clock::now();

    cout << "Legrövidebb út: " << total_distance << endl;
    output_file << "Legrövidebb út: " << total_distance << endl;
    cout << "Útvonal:";
    output_file << "Útvonal:";
    for (City &city : cities)
    {
        cout << " " << city.id;
        output_file << " " << city.id;
    }
    cout << " " << cities.front().id << endl;
    output_file << " " << cities.front().id << endl;
    // auto duration = duration_cast<seconds>(stop - start);

    // cout << "Ido: " << duration.count() << " masodperc" << endl;

    return 0;
}