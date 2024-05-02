//CS311 graph.h
//INSTRUCTION:
//undirected graph class - header file template
//You should always add comments to each function to describe its PURPOSE and PARAMETERS
#pragma once
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <iostream>
#include <stack>
using namespace std;

class City {
public:
    // The index of the vertex. starting from 0
    int id;
	// The City_Code of the City. Additional attributes can be added
	string City_Code;
    // The name of the City. Additional attributes can be added
    string name;
	//Population of the city
	long population;
	//Elevation of the city
	int elevation;

    // Default constructor
    City() {
        id = 0;
		City_Code = "";
        name = "";
        population = -1;//city could have a population of 0. RIP
		elevation = -1000000;//Elevation of city will be risen from the depths of hell upon it's creation. Praise be to C++! (This is a joke)
		
    }

    // Constructor
    City(int id, string City_Code, string name, long population,  int elevation) {
        this->id = id;
		this->City_Code = City_Code;
        this->name = name;
		this->population = population;
		this->elevation = elevation;
    };
	
	void printCity(){
	cout<<" ["<<id<<"]"<<name<<" ("<<City_Code<<"), population "<<population<<", elevation "<<elevation<<endl;
	}

    // Overloading of equality operator
    bool operator==(const City &other) const {
        // Two cities are equal if they have the same ID
        return (id == other.id);
    }
	
	//City& operator= (const City& city);

    // This overloads cout for the City object
    // This is a friend function 
    friend ostream &operator<<(ostream &, const City & city);

    // This overloads cin for the City object
    // This is a friend function
    friend istream &operator>>(istream &, City & city);
};

/**
 * @brief city class. It represents an road from one vertex to another
 * 
 */
struct Road {
    int from_city; // The index of the city/vertex where the road/edge starts
    int to_city; // index of the city/vertex where the road/edge ends.
    int length; // The length/weight of the road/edge. Additional attributes can be added

    Road(int from_city = 0, int to_city = 0, int length = 0) {
        this->from_city = from_city;
        this->to_city = to_city;
        this->length = length;
    }
	
	void printRoad(){
		cout << "->|From: "<<from_city<<" -To: "<<to_city<<" -Length "<<length<<"|\n";
	}
	
	// This overloads cout for the City object
    // This is a friend function 
    friend ostream &operator<<(ostream &, const Road & road);

    // This overloads cin for the City object
    // This is a friend function
    friend istream &operator>>(istream &, Road & road);
};

/**
 * @brief Graph class
 *
 */
class Graph
{
public:
    int numCities;    // No. of vertices
    vector<City> cities; // The list of cities
	//adjList is used to get the OUTGOING roads from any city
	//adjListRev is used to get the INCOMING roads for any city
    vector<vector<Road>> adjList, adjListRev; // The adjacency list

    // Default constructor. Create an empty graph
    Graph() {
        numCities = 0;
    }

    // Constructor. Create a graph with n vertices
    Graph(int n);

    // Destructor
    ~Graph();
	
	/**
	* @brief Load cities from a file
	*
	* @param file_name The name of the file to load
	*/
	void fillCitiesTable(string file_name);
	
	void fillRoadsTable(string file_name);
	
	bool findCity(string City_Code, City &returnCity);

    /**
     * @brief Add a vertex to the graph
     * @param v The vertex to be added
     */
    void addVertex();

    /**
     * @brief Add a directed road from v1 to v2 to the graph
     *
     * @param v1 The index of the vertex where the road starts
     * @param v2 The index of the vertex where the road ends
     * @param length The length of the city
     */
    void addDirectedEdge(Road r);

    /**
     * @brief Add an undirected city to the graph. An undirected city is represented by two directed edges.
     * @param v1 The index of the first vertex
     * @param v2 The index of the second vertex
     */
     void addUndirectedEdge(Road r);

    /**
     * @brief the number of outgoing edges from vertex v
     * @param v The index of the vertex
     * @return The number of outgoing edges from the vertex
     */
    int outDegree(int v);

    /**
     * @brief Depth first search
     *
     * @param v The index of the vertex where the search starts
     * @return The list of vertices in the order they are visited
     */
    vector<int> DepthFirstSearch(int start);
	
	void recursiveDFS(vector<int> &DFStraversal, vector<bool> &visited, stack<int> &list);
	
	bool pathCheck(int from, int to);
	
	void DijkstrasPath(int start, vector<Road> &thePaths);
	
	void shortestPath(int start, int end, vector<Road> thePaths);

    /**
     * @brief Breadth first search
     *
     * @param v The index of the vertex where the search starts
     * @return The list of vertices in the order they are visited
     */
    vector<int> BreadthFirstSearch(int start, int end);

    /**
     * @brief Check if the undirected graph contains cycles
     * @return true if the graph has cycles
     */
    bool checkCycle();
	
	bool checkCycleRecursive(int u, vector<bool>& visited, int parent);

    /**
      * @brief Print the graph
      */
    void printGraph();
	
	void printCities();//used to print all cities and all of their information (pulls from Cities vector)
	
	void printRoads();//used to print all cities and all of their adjacent cities (pulls fom adjList Vector)

};