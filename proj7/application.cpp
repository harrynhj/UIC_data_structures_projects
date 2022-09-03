// application.cpp <Starter Code>
// Haoji Ni
//
// University of Illinois at Chicago
// CS 251: Spring 2022
// Project #7 - Openstreet Maps
//

/*
                       CREATIVE COMPONENT
                        TITLE: I'm tired
    DESCRIPTION: Assume person 2 is tired and don't want walk,
    program will find the shortest path from person 1 to person 2,
    and will not meet at middle point building.
    INSTRUCTIONS:
    1. Input the map file
    2. Select option 'c' to enter creative component
    3. Input person 1's building location
    4. Input person 2's building location
    5. Input who is tired, input should be "1" or "2"
    6. It will display the path from 1 to 2 or 2 to 1 and distance
    7. If there is no path, program will ask you to walk on grass
    8. Once you are done, you can input "#" to exit
*/

// References:
// TinyXML: https://github.com/leethomason/tinyxml2
// OpenStreetMap: https://www.openstreetmap.org
// OpenStreetMap docs:
//   https://wiki.openstreetmap.org/wiki/Main_Page
//   https://wiki.openstreetmap.org/wiki/Map_Features
//   https://wiki.openstreetmap.org/wiki/Node
//   https://wiki.openstreetmap.org/wiki/Way
//   https://wiki.openstreetmap.org/wiki/Relation

#include <iostream>
#include <iomanip>  /*setprecision*/
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <limits>
#include <queue>
#include <algorithm>
#include <stack>

#include "tinyxml2.h"
#include "dist.h"
#include "osm.h"
#include "graph.h"

using namespace std;
using namespace tinyxml2;

// global variables for infinity number
const double INF = numeric_limits<double>::max();

// Class for priority queue sorting
class prioritize {
public:
  bool operator()(const pair<long long, double> &p1, const pair<long long, double> &p2) {
    if (p1.second == p2.second) {
      return p1.first > p2.first;
    }
    return p1.second > p2.second;
  }
};

// Helper function for application
// This function will return BuildingInfo
// Based on the user input
bool searchBuilding(string user_query, vector<BuildingInfo> buildings,
                    BuildingInfo& result) {
    // First find by using abbreviation
    for (auto & i : buildings) {
        if (i.Abbrev == user_query) {
            result = i;
            return true;
        }
    }
    // if not found, try search by full name
    for (auto & i : buildings) {
        if (i.Fullname.find(user_query) != string::npos) {
            result = i;
            return true;
        }
    }
    // if still can't find it, return false
    return false;
}

// Helper function for application
// This function will calculate the shortest distance
// between coordinates to the building
BuildingInfo findNearestBuilding(Coordinates cord, const vector<BuildingInfo>& buildings,
                                 vector <string>& usedBuildings) {
    // initialize variables
    double min = INF;
    BuildingInfo result;

    // loop through all buildings
    for (auto i : buildings) {
        // calculate distance
        double distance = distBetween2Points(cord.Lat, cord.Lon,
                                             i.Coords.Lat, i.Coords.Lon);
        // update the result
        if (distance < min) {
            // check if the building has been used
            if (find(usedBuildings.begin(), usedBuildings.end(), i.Fullname) == usedBuildings.end()) {
                min = distance;
                result = i;
            }
        }
    }
    // save the building name to usedBuildings
    usedBuildings.push_back(result.Fullname);
    return result;
}

// Helper function for application
// This function will return the nearest node to the building
long long nearestNode(BuildingInfo b, vector<FootwayInfo>& Footways,
                      map<long long, Coordinates>& Nodes) {
    // initialize variables
     double min = INF;
     double distance;
     long long result;
     // loop through all footways and find the nearest node
     for (auto & Footway : Footways) {
         for (long long & Node : Footway.Nodes) {
             // calculate distance
             distance = distBetween2Points(b.Coords.Lat, b.Coords.Lon,
                                           Nodes[Node].Lat,
                                           Nodes[Node].Lon);
             if (distance < min) {
                 min = distance;
                 result = Node;
             }
         }
     }
     return result;
}

// Helper function for application
// This function will return the nearest path
vector<long long> Dijkstra(graph<long long, double> G, long long startV,
                           map<long long, double>& distances,
                           map<long long, long long>& predecessors) {
    // initialize variables
    vector<long long> visited;
    vector<long long> v_list = G.getVertices();
    priority_queue<pair<long long, double>, vector<pair<long long, double>>, prioritize> unvisited_queue;
    double edgeWeight = 0;
    double alt_distance = 0;

    // set all distances to infinity, pre to 0
    for (int i = 0; i < G.NumVertices(); i++) {
        distances[v_list[i]] = INF;
        unvisited_queue.push(make_pair(v_list[i], INF));
        predecessors[v_list[i]] = 0;
    }

    distances[startV] = 0;
    unvisited_queue.push(make_pair(startV, 0));
    // loop until all vertices are visited
    while (!unvisited_queue.empty()) {
        long long currentV = unvisited_queue.top().first;
        unvisited_queue.pop();
        // if currentV is INF, stop
        if (distances[currentV] == INF) {
            break;
        } else if (find(visited.begin(), visited.end(), currentV) != visited.end()) {
            // if currentV is in visited, skip
            continue;
        } else {
            // if currentV is not in visited, add to visited
            visited.push_back(currentV);
        }
        // get all adjacent vertices
        set <long long> neighbors = G.neighbors(currentV);
        // loop through all adjacent vertices
        for (auto neighbor : neighbors) {
            edgeWeight = INF;
            G.getWeight(currentV, neighbor, edgeWeight);
            alt_distance = distances[currentV] + edgeWeight;
            // if the distance is shorter, update the distance
            if (alt_distance < distances[neighbor]) {
                distances[neighbor] = alt_distance;
                unvisited_queue.push(make_pair(neighbor, alt_distance));
                predecessors[neighbor] = currentV;
            }
        }
    }
    return visited;
}

// Helper function for application
// This function will return the shortest path
// as a vector of long longs
vector <long long> getPath(map<long long, long long>& predecessors,
                               long long endV) {
    // initialize variables
    vector <long long> path;
    stack <long long> temp;
    long long currentV = endV;
    // while the currentV is not 0, push to stack
    while (currentV != 0) {
        temp.push(currentV);
        currentV = predecessors[currentV];
    }
    // push path to vector
    while (!temp.empty()) {
        path.push_back(temp.top());
        temp.pop();
    }
    return path;
}

// Helper function for application
// It will print out information about the building
void printLocation(const BuildingInfo& location) {
    cout << " " << location.Fullname << endl;
    cout << " (" << location.Coords.Lat << ", " << location.Coords.Lon << ")" << endl;
}

// Helper function for application
// It will print out the nearest nodes
void printNearest(const map<long long, Coordinates>& Nodes, long long id) {
    cout << " " << id << endl;
    cout << " (" << Nodes.at(id).Lat << ", " << Nodes.at(id).Lon << ")" << endl;
}

// Helper function for application
// It will print out the path from start to end
void printPath(const vector<long long>& path) {
    cout << "Path: ";
    for (int i = 0; i < path.size(); i++) {
        // if it's the last element, do not print ->
        if (i == path.size() - 1) {
            cout << path[i];
        } else {
            cout << path[i] << "->";
        }
    }
    cout << endl;
}

// Creative Component functions
void creative(map<long long, Coordinates>& Nodes, vector<FootwayInfo>& Footways,
              vector<BuildingInfo>& Buildings, graph<long long, double> G) {
    string person1Building, person2Building, tired;

    // get person 1 building
    cout << endl;
    cout << "Enter person 1's building (partial name or abbreviation), or #> ";
    getline(cin, person1Building);

    while (person1Building != "#") {
        // get person 2 building
        cout << "Enter person 2's building (partial name or abbreviation)> ";
        getline(cin, person2Building);

        // get who is tired
        cout << "Who is tired? (enter 1 or 2)> ";
        getline(cin, tired);

        BuildingInfo p1Info, p2Info;
        // use function pass by reference to record the building info
        // also check if the building is existed
        // if is not found, will skip to next loop
        if (!searchBuilding(person1Building, Buildings, p1Info)) {
            cout << "Person 1's building not found" << endl;
        } else if (!searchBuilding(person2Building, Buildings, p2Info)) {
            cout << "Person 2's building not found" << endl;
        } else {
            // find the nearest node to 3 points
            long long p1Node = nearestNode(p1Info, Footways, Nodes);
            long long p2Node = nearestNode(p2Info, Footways, Nodes);

            cout << endl;

            // Dijkstra's algorithm and output
            // initialize the graph variables
            map<long long, double> distances1;
            map<long long, long long> pre1;
            map<long long, double> distances2;
            map<long long, long long> pre2;

            // call Dijkstra function
            vector<long long> p1_Dijkstra =
                    Dijkstra(G, p1Node, distances1, pre1);
            vector<long long> p2_Dijkstra =
                    Dijkstra(G, p2Node, distances2, pre2);

            if (distances1[p2Node] == INF) {
                // if is not connected, exit the loop
                cout << "Sorry, destination unreachable." << endl;
                cout << "Try walk on grass?" << endl;
            } else {
                // get the path for p1 and p2
                if (tired == "1") {
                    // if person 1 is tired, use the path for p2
                    vector<long long> path = getPath(pre2, p1Node);
                    cout << "Person 2's distance to Person 1: ";
                    cout << distances2[p1Node] << endl;
                    printPath(path);
                } else {
                    // if person 2 is tired, use the path for p1
                    vector<long long> path = getPath( pre1, p2Node);
                    cout << "Person 1's distance to Person 2: ";
                    cout << distances1[p2Node] << endl;
                    printPath(path);
                }
            }
        }
        // another navigation
        cout << endl;
        cout << "Enter person 1's building (partial name or abbreviation), or #> ";
        getline(cin, person1Building);
    }
}

// Implement your standard application here
void application(
    map<long long, Coordinates>& Nodes, vector<FootwayInfo>& Footways,
    vector<BuildingInfo>& Buildings, graph<long long, double> G) {
  string person1Building, person2Building;

  // get person 1 building
  cout << endl;
  cout << "Enter person 1's building (partial name or abbreviation), or #> ";
  getline(cin, person1Building);


  while (person1Building != "#") {
      // get person 2 building
    cout << "Enter person 2's building (partial name or abbreviation)> ";
    getline(cin, person2Building);

    // lookup buildings, find nearest start and dest nodes, find center
    BuildingInfo p1Info, p2Info, middleInfo;
    // use function pass by reference to record the building info
    // also check if the building is existed
    // if is not found, will skip to next loop
    if (!searchBuilding(person1Building, Buildings, p1Info)) {
        cout << "Person 1's building not found" << endl;
    } else if (!searchBuilding(person2Building, Buildings, p2Info)) {
        cout << "Person 2's building not found" << endl;
    } else {
        // calculate the middle point
        Coordinates middle = centerBetween2Points(p1Info.Coords.Lat,
                                                  p1Info.Coords.Lon,
                                                  p2Info.Coords.Lat,
                                                  p2Info.Coords.Lon);

        // find the nearest building to the middle point
        // Create a vector for searched buildings
        vector <string> used_b;
        middleInfo = findNearestBuilding(middle, Buildings, used_b);

        // find the nearest node to 3 points
        long long p1Node = nearestNode(p1Info, Footways, Nodes);
        long long p2Node = nearestNode(p2Info, Footways, Nodes);
        long long middleNode = nearestNode(middleInfo, Footways, Nodes);

        cout << endl;

        // print building info
        cout << "Person 1's point:" << endl;
        printLocation(p1Info);
        cout << "Person 2's point:" << endl;
        printLocation(p2Info);
        cout << "Destination Building:" << endl;
        printLocation(middleInfo);

        cout << endl;

        // print nearest nodes
        cout << "Nearest P1 node:" << endl;
        printNearest(Nodes, p1Node);
        cout << "Nearest P2 node:" << endl;
        printNearest(Nodes, p2Node);
        cout << "Nearest destination node:" << endl;
        printNearest(Nodes, middleNode);

        cout << endl;

        // Dijkstra's algorithm and output
        // use flag variable to control loop
        int flag = 0;
        while (flag == 0) {
            // initialize the graph variables
            map<long long, double> distances1;
            map<long long, long long> pre1;
            map<long long, double> distances2;
            map<long long, long long> pre2;

            // call Dijkstra function
            vector<long long> p1_Dijkstra = Dijkstra(G, p1Node, distances1, pre1);
            vector<long long> p2_Dijkstra = Dijkstra(G, p2Node, distances2, pre2);

            if (distances1[p2Node] == INF) {
                // if is not connected, exit the loop
                cout << "Sorry, destination unreachable." << endl;
                flag = 1;
            } else if (distances1[middleNode] >= INF || distances2[middleNode] >= INF) {
                // when p1 or p2 is not connected to the middle point
                cout << "At least one person was unable to reach the destination building.";
                cout << " Finding next closest building..." << endl;

                // find the next closest building
                middleInfo = findNearestBuilding(middle, Buildings, used_b);
                middleNode = nearestNode(middleInfo, Footways, Nodes);

                // output the new building info
                cout << "New destination building:" << endl;
                printLocation(middleInfo);
                cout << "Nearest destination node:" << endl;
                printNearest(Nodes, middleNode);

            } else {
                // normal situation
                // get the path for p1 and p2
                vector <long long> p1_path = getPath(pre1, middleNode);
                vector <long long> p2_path = getPath(pre2, middleNode);

                cout << "Person 1's distance to dest: " << distances1[middleNode] << " miles" << endl;
                printPath(p1_path);
                cout << "Person 2's distance to dest: " << distances2[middleNode] << " miles" << endl;
                printPath(p2_path);

                // exit the loop
                flag = 1;
            }
        }
    }

    // another navigation
    cout << endl;
    cout << "Enter person 1's building (partial name or abbreviation), or #> ";
    getline(cin, person1Building);
  }
}

int main() {
  // maps a Node ID to it's coordinates (lat, lon)
  map<long long, Coordinates>  Nodes;
  // info about each footway, in no particular order
  vector<FootwayInfo>          Footways;
  // info about each building, in no particular order
  vector<BuildingInfo>         Buildings;
  XMLDocument                  xmldoc;

  cout << "** Navigating UIC open street map **" << endl;
  cout << endl;
  cout << std::setprecision(8);

  string def_filename = "map.osm";
  string filename;

  cout << "Enter map filename> ";
  getline(cin, filename);

  if (filename == "") {
    filename = def_filename;
  }

  // Load XML-based map file
  if (!LoadOpenStreetMap(filename, xmldoc)) {
    cout << "**Error: unable to load open street map." << endl;
    cout << endl;
    return 0;
  }

  // Read the nodes, which are the various known positions on the map:
  int nodeCount = ReadMapNodes(xmldoc, Nodes);

  // Read the footways, which are the walking paths:
  int footwayCount = ReadFootways(xmldoc, Footways);

  // Read the university buildings:
  int buildingCount = ReadUniversityBuildings(xmldoc, Nodes, Buildings);

  // Stats
  assert(nodeCount == (int)Nodes.size());
  assert(footwayCount == (int)Footways.size());
  assert(buildingCount == (int)Buildings.size());

  cout << endl;
  cout << "# of nodes: " << Nodes.size() << endl;
  cout << "# of footways: " << Footways.size() << endl;
  cout << "# of buildings: " << Buildings.size() << endl;

  // create graph
  graph <long long, double> G;

  // add vertices
  for (auto it = Nodes.begin(); it != Nodes.end(); ++it) {
    G.addVertex(it->first);
  }

  // add edges
  double distance = 0.0;
  for (auto it = Footways.begin(); it != Footways.end(); ++it) {
      // loop through all the nodes to calculate the distance
    for (int i = 0; i < it->Nodes.size()-1; i++) {
        // use function to calculate the distance
      distance = distBetween2Points(Nodes[it->Nodes[i]].Lat ,
                                    Nodes[it->Nodes[i]].Lon ,
                                    Nodes[it->Nodes[i+1]].Lat ,
                                    Nodes[it->Nodes[i+1]].Lon);
      // add edge on both sides
      G.addEdge(it->Nodes[i], it->Nodes[i+1], distance);
      G.addEdge(it->Nodes[i+1], it->Nodes[i], distance);
    }
  }
  cout << "# of vertices: " << G.NumVertices() << endl;
  cout << "# of edges: " << G.NumEdges() << endl;
  cout << endl;



  // Menu
  string userInput;
  cout << "Enter \"a\" for the standard application or "
        << "\"c\" for the creative component application> ";
  getline(cin, userInput);
  if (userInput == "a") {
    // call the application
    application(Nodes, Footways, Buildings, G);
  } else if (userInput == "c") {
    // call the creative component
    creative(Nodes, Footways, Buildings, G);
  }

  // done:
  cout << "** Done **" << endl;
  return 0;
}
