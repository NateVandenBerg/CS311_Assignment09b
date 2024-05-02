#include <iostream>
#include<fstream>
#include "graph.h"

void studentInfo() {
    cout << "\n Authors: Nathaniel VandenBerg\n\t  Caprice Jardin\n\t  Anna Jensen\n";
    cout << " Date: \t12/07/2022\n Course: \tCS311 (Data structures and Algorithms)\n";
    cout << " Description: Program to find the shortest route between cities\n";
    cout << "----------------------------------------------------------------\n";
}

int main(int argc, char** argv) {
    Graph g(0);
    /*
    //Used to test all if any city is connected to another city
    ifstream fin;
    fin.open("city.txt");
    if (!fin) {
        cout << "Error opening file " << "city.txt" << endl;
        return 0;
    }
    vector<City> Cities;
    City city;
    if (!fin.good()) throw "I/O error";
    while (fin >> city) {
        Cities.push_back(city);
    }
    fin.close();

    g.fillCitiesTable("city.txt");
    g.fillRoadsTable("road.txt");

    for (auto start : Cities) {
        cout << "\n---------------------------------------\n";
        vector<int> list = g.DepthFirstSearch(start.id);

        for (auto end : Cities) {
            cout << "\n---------------------------------------\n";
            if (g.pathCheck(start.id, end.id)) {
                cout << " From City:\t";
                start.printCity();
                cout << " To City:\t";
                end.printCity();

                vector<Road> thePaths(g.numCities);

                //run to find shortest path from start to all connecting cities
                g.DijkstrasPath(start.id, thePaths);
                //get the shortestpath and print
                g.shortestPath(start.id, end.id, thePaths);
            }
            else {
                cout << "\nNo route from " << start.name << " to " << end.name << endl << endl;
            }           
            cout << "\n---------------------------------------";           
        }
     //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^   
    }//Used to test all if any city is connected to another city*/
    
    studentInfo();
    //if function is called w/o command line end program
    if (argc < 2) {
        cout << "This program needs a command line arguement!\n";
        return 0;
    }
    
    // Read the cities in the "city.txt" file
    //add all the cities from the .txt file to the g.cities vector
    g.fillCitiesTable("city.txt");
    //add all the roads from the .txt file to the g.adjList and g.adjListRev vectors
    g.fillRoadsTable("road.txt");
    //g.printCities();
    //g.printRoads();
    City start,end;
    //check that the start city exist and get the index value for the city
    if (!g.findCity(argv[1], start)) {
        cout << "Invalid city code: " << argv[1] << endl;
        return 0;
    }
    //check that the end city exist and get the index value for the city
    if (!g.findCity(argv[2], end)) {
        cout << "Invalid city code: " << argv[2] << endl;
        return 0;
    }

    //check to make sure there is a route from start to end
    //when running the shortest path algorithm can probably remove functon
    if (!g.pathCheck(start.id, end.id)) {
        cout << "\nNo route from " << start.name << " to " << end.name << endl<<endl;
        return 0;
    }

    cout << " From City:\t";
    start.printCity();
    cout << " To City:\t";
    end.printCity();

    vector<Road> thePaths(g.numCities);
    
    //run to find shortest path from start to all connecting cities
    g.DijkstrasPath(start.id, thePaths);
    
    //for (int i = 0; i < g.numCities;i++) {
    //    cout << i << " ";
    //    thePaths[i].printRoad();
    //}
    //get the shortestpath and print
    g.shortestPath(start.id, end.id, thePaths);
    
    return 0;
}