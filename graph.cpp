#include "graph.h"
//#include "city.h"
#include <unordered_map>
#include <fstream>
#include <limits.h>
using namespace std;

// @brief Construct a Graph with the given number of cities.
// @param nV The number of cities in the graph.
Graph::Graph(int nV) {
    numCities = nV;
    cities = vector<City>(numCities);
    adjList = vector<vector<Road>>(numCities);
    //adjListRev = vector<vector<Road>>(numCities);
}

// @brief destructor
Graph::~Graph() {
    cities.clear();
    //adjList is used to get the OUTGOING roads from any city
    adjList.clear();
    //adjListRev is used to get the INCOMING roads for any city
    //adjListRev.clear();
    //Both adjList and adjListRev have the exact same road/edges they are just organized differently

}

/**
 * @brief Load cities from a file
 *
 * @param file_name The name of the file to load
 */
void Graph::fillCitiesTable(string file_name) {
    // Open the file to read
    //cout << ">fillTable();\n";
    ifstream fin;
    // Open the file to read
    fin.open(file_name.c_str());
    if (!fin) {
        cout << "Error opening file " << file_name << endl;
        return;
    }

    City city;
    if (!fin.good()) throw "I/O error";
    while (fin >> city) {
        //add city to cities vector
        cities.push_back(city);
        //create blank road list for the added city
        vector<Road> newRoadList1, newRoadList2;
        //add the blank road list to the adjList
        adjList.push_back(newRoadList1);
        //add the blank road list to the adjListRev
        //adjListRev.push_back(newRoadList2);
        numCities++;
    }
    fin.close();
}
void Graph::fillRoadsTable(string file_name) {
    // Open the file to read
    //cout << ">fillRoadsTable();\n";
    ifstream fin;
    fin.open(file_name.c_str());
    if (!fin) {
        cout << "Error opening file " << file_name << endl;
        return;
    }

    Road road;
    if (!fin.good()) throw "I/O error";
    while (fin >> road) {
        //add the road/edge for the to the adjList and adjListRev
        addDirectedEdge(road);
    }
    fin.close();
}

// @brief add a City to the graph
void Graph::addVertex() {
    for (auto r : cities) {
        vector<Road> newRoadList;
        //create new vector of type edge in the adjList vector
        adjList.push_back(newRoadList);
        //adjListRev.push_back(newRoadList);
        numCities++;
    }
}

// @brief add a directed road v1->v2 to the graph
void Graph::addDirectedEdge(Road r) {
    //cout << "\naddDirectedGraph";
    //check if road has already been added
    //Traverse the vector    
    for (auto it : adjList[r.from_city]) {
        //check if road already exists
        //it.printRoad();
        if (r.to_city == it.to_city &&
            r.length == it.length) {
            return;//do nothing if road already exists
        }
    }
    //push Road onto to adjList and adjListRev
    adjList[r.from_city].push_back(r);
    //adjListRev[r.to_city].push_back(r);
}

// @brief add an undirected Road to the graph
void Graph::addUndirectedEdge(Road r) {
    //Add Road v1->v2
    addDirectedEdge(r);

    //create duplicate road
    Road s;
    //swap to and from cities
    s.to_city = r.from_city;
    s.from_city = r.to_city;
    s.length = r.length;
    //Add Road
    addDirectedEdge(s);
}

// @brief the number of outgoing Roads from a city
int Graph::outDegree(int c) {
    //return the number of Roads coming from the vector
    return adjList[c].size();
}

//check to make sure the city exists
bool Graph::findCity(string City_Code, City &returnCity) {
    //traveres the cities vector
    for (auto c : cities) {
        //if the City_Code exists 
        if (City_Code == c.City_Code) {
            //update the returnCity object to that city
            returnCity = c;
            //return true when found
            return true;
        }
    }
    //otherwise return false
    return false;
}

bool Graph::pathCheck(int start, int end) {
    //at the start city run dfs to find all connected cities
    vector<int> list = DepthFirstSearch(start);
    //for the dfs list
    for (auto i : list) {
        //if the end city index is in the dfs list return true
        if (end == i) {
            return true;
        }
    }
    return false;
}

void Graph::DijkstrasPath(int start, vector<Road> &thePaths) {
    //record the total distance from the starting city to all other cities
    //set all city distances to infinity
    vector<int> distance(numCities,INT_MAX);
    //used to get the next city to visit
    queue<int> nextCity;
    //used to keep track of what cities have already been visited
    vector<bool>visited(numCities);
    //set the distance of the starting city to 0
    distance[start] = 0;
    visited[start] = true;
    //add the starting city to the queue
    nextCity.push(start);
    while (!nextCity.empty()) {
        //get the next city to be visited from the queue
        int curr = nextCity.front();
        //mark current city as visited
        visited[curr] = true;
        //remove the city from the queue
        nextCity.pop();
        //chech the adjacent cities
        for (auto r : adjList[curr]) {
            //if the adjacent city has not been visited yet
            if (!visited[r.to_city]) {
                //add adjacent city to the cities to be visited
                nextCity.push(r.to_city);
            }
            //if a shorter distance is found to the current city
            if (distance[r.to_city] > distance[curr] + r.length) {
                //update the distance to the current city
                distance[r.to_city] = distance[curr] + r.length;
                //add the road to the thePath vector pointing to where the road came from
                thePaths[r.to_city] = r;
            }
            
        }
    }
}

void Graph::shortestPath(int start, int end, vector<Road> thePaths) {
    //create stack for the adjacent cities
    stack<Road> theShortestPath;
    //index value for the connecting city starting at the end
    int from = end;
    //total length of the distance traveled starting at 0
    int length = 0;
    //starting from the ending city until the starting city is reached
    while (from != start) {
        //increase the length
        length += thePaths[from].length;
        //push the previous city to the stack
        theShortestPath.push(thePaths[from]);
        //get the next city in the path 
        from = thePaths[from].from_city;
        
    }
    cout << "\n The shortest distance from " << cities[start].name << " to " << cities[end].name << " is " << length;
    cout << "\n through the route: ";
    while (!theShortestPath.empty()) {
        cout << cities[theShortestPath.top().from_city].name
            << " [" << theShortestPath.top().from_city << "] -> ";
        theShortestPath.pop();
    }
    cout << cities[end].name << " [" << end << "] " << endl;
}

// @brief depth first search from city c
vector<int> Graph::DepthFirstSearch(int start) {
    //create the traveral list
    vector<int> DFStraversal;
    //create a list for vertices that have been visited
    vector<bool> visited(numCities, false);
    //create a stack of vertices that need to be visited
    std::stack<int> list;
    //add start vertex to list
    list.push(start);
    //run DFS recursively
    recursiveDFS(DFStraversal, visited, list);

    return DFStraversal;
}

void Graph::recursiveDFS(vector<int>& DFStraversal, vector<bool>& visited, std::stack<int>& list) {
    //as long as the stack is not empty
    while (!list.empty()) {
        //get the top vertex from the stack
        int curr = list.top();
        //remove the vertex from the stack
        list.pop();
        //set the vertex as visited
        visited[curr] = true;
        //add the vertex as part of the traversal
        DFStraversal.push_back(curr);
        //traverse the adjacent edge list
        for (auto it : adjList[curr]) {
            //if that vertex has not been visited yet
            if (!visited[it.to_city]) {
                //add the vertex to the stack
                list.push(it.to_city);
                //recursively call DFS at this vertex
                recursiveDFS(DFStraversal, visited, list);
            }
        }
    }
}

// @brief breadth first search from a city
vector<int> Graph::BreadthFirstSearch(int start, int end) {
    //List of cities traversed
    vector<int> BFStraversal;
    //used to check if vetex has been visited already
    vector<bool> visited(numCities, false);
    //create queue of Cities to be visited
    queue<int> frontierQueue;
    //mark starting city as visited
    visited[start] = true;
    //add starting city to queue
    frontierQueue.push(start);

    int curr = frontierQueue.front();

    while (!frontierQueue.empty()) {
        if (curr != end) {
            //remove it from the queue
            frontierQueue.pop();
            //add the visited city to the traversal list
            BFStraversal.push_back(curr);
            //at the current city get the adjacent cities
            for (auto it : adjList[curr]) {
                //if this adjacent city has not been visited
                if (!visited[it.to_city]) {
                    //update the city as visited
                    visited[it.to_city] = true;
                    //add the city to the queue
                    frontierQueue.push(it.to_city);
                }
            }
            //get next city from the queue
            curr = frontierQueue.front();
        }
        else {
            BFStraversal.push_back(curr);
            return BFStraversal;
        }
            
        
    } 
    return BFStraversal;
}

/**
 * @brief Check if the graph has cycles
 * @return true if the graph has cycles
 */
bool Graph::checkCycle() {
    //traverse cities vector
    for (auto c : cities) {
        //create a list for cities that have been visited
        vector<bool> visited(numCities, false);
        //if the city has not been visited yet
        if (!visited[c.id])
            //check of the graph at the city has a loop
            if (checkCycleRecursive(c.id, visited, -1))
                //return true if it does
                return true;
    }
    //else return false
    return false;
}

bool Graph::checkCycleRecursive(int c, vector<bool>& visited, int parent) {
    //set the city as visited
    visited[c] = true;
    //traverse the adjacent Road list
    for (auto it : adjList[c]) {
        //if the adjacent city has not been visited yet
        if (!visited[it.to_city]) {
            //check if the graph of the adjacnet city contains a loop
            if (checkCycleRecursive(it.to_city, visited, c))
                //if it does return true
                return true;
        }
        //otherwise, if the adjacent city in not the parent city
        else if (it.to_city != parent)
            //return true
            return true;
    }
    //else return false
    return false;
}

// @brief print the graph
void Graph::printGraph() {
    cout << "Graph:" << endl;
    for (auto c : cities) {
        cout << cities[c.id].name << ": ";
        for (auto r : adjList[c.id]) {
            cout << r.to_city << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Graph::printCities() {
    cout << "Cities:" << endl;
    for (auto c : cities) {
        cout << "\t";
        c.printCity();
    }
    cout << endl;
}

void Graph::printRoads() {
    //cout << "printRoads:" << endl;//used to show function has been called comment out later
    for (auto c : cities) {
        cout << c.name <<" " << c.id << " connects to " << outDegree(c.id) << " towns:\n";
        for (auto r : adjList[c.id]) {
            cout << "\t" << "Distance: " << r.length;
            cities[r.to_city].printCity();
            //r.printRoad();
        }
    }
    
    cout << endl;
}
/*
City& City::operator= (const City& city) {
    this->id = city.id;
    this->City_Code = city.City_Code;
    this->name = city.name;
    this->population = city.population;
    this->elevation = city.elevation;
    return *this;
}*/

// overload outs << for City
ostream& operator<<(ostream& os, const City& city) {
    os << "->|" << city.id << "-" << city.City_Code << "-" << city.name << "-" << city.population << "-" << city.elevation << "| ";
    return os;
}

// overload ins >> for City
istream& operator>>(istream& is, City& city) {
    is >> city.id >> city.City_Code >> city.name >> city.population >> city.elevation;
    return is;
}

// overload outs << for Road
ostream& operator<<(ostream& os, const Road& road) {
    os << "->|" << road.from_city << "-" << road.to_city << "-" << road.length << "|";
    return os;
}

// overload ins >> for Road
istream& operator>>(istream& is, Road& road) {
    is >> road.from_city >> road.to_city >> road.length;
    return is;
}
