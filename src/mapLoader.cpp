#include <iostream>
#include <fstream>
#include <cstdlib>
#include <list>
#include <queue>
#include <vector>
#include <algorithm>
#include "mapLoader.h"

using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::to_string;
using std::pair;
using std::priority_queue;

# define INF 0x3f3f3f3f
typedef pair<int, int> iPair;

CityNode::CityNode() {
	next = NULL;
}  //default constructor

CityNode::CityNode(int theID) {
	ID = theID;
	name = "";
	region = "Area_" + to_string(theID / 7 + 1);  //7 cities in one region
	//step1Price = 10;
	//step2Price = 15;
	//step3Price = 20;
	distance = 0;
	
	//owner1 = "no player";
	//owner2 = "no player";
	//owner3 = "no plyaer";
	next = NULL;
}

CityNode::CityNode(const CityNode &cn) {
	ID = cn.ID;
	name = cn.name;
	region = cn.region;
	//step1Price = cn.step1Price;
	//step2Price = cn.step2Price;
	//step3Price = cn.step3Price;
	distance = cn.distance;
	owners = vector<string>(cn.owners);
	//owner1 = cn.owner1;
	//owner2 = cn.owner2;
	//owner3 = cn.owner3;
	next = NULL;
}

CityNode* CityNode::operator=(const CityNode *cn) {
	//cout << "cn operator = is called!\n";
	if (this == cn)
		return this;

	ID = cn->ID;
	name = cn->name;
	region = cn->region;
	//step1Price = cn->step1Price;
	//step2Price = cn->step2Price;
	//step3Price = cn->step3Price;
	distance = cn->distance;
	owners = vector<string>(cn->owners);
	next = NULL;
	return this;
}


AdjList::AdjList() {
	base = NULL;
	head = NULL;
} //default constructor
AdjList::AdjList(const AdjList &al) {
	if (al.head == NULL)
		head = NULL;
	else {

		base = new CityNode(*al.base);
		head = new CityNode(*al.head); //create a copy's head using original's head
		CityNode *current = head;
		CityNode *alCurrent = al.head;
		while (alCurrent->next != NULL) {
			current->next = new CityNode(*alCurrent->next);
			alCurrent = alCurrent->next;
			current = current->next;
		}
	}
}

AdjList& AdjList::operator=(const AdjList &al) {
	//cout << "al operator = is called!\n";
	if (this == &al)
		return *this;

	//cout << "al base: " << al.base->name << endl;
	base = new CityNode(*al.base);
	//cout << "copy base: " << base->name << endl;
	//cout << "al head: " << al.head->name << endl;
	head = new CityNode(*al.head); //create a copy's head using original's head
	//cout << "copy head: " << base->name << endl;
	CityNode *current = head;
	CityNode *alCurrent = al.head;
	while (alCurrent->next != NULL) {
		current->next = new CityNode(*alCurrent->next);
		alCurrent = alCurrent->next;
		current = current->next;
	}
	return *this;
}


Graph::Graph() {} //default constructor

Graph::Graph(int theSize)
{
	size = theSize;

	arr = new AdjList[theSize];
	for (int i = 0; i < theSize; i++) {
		arr[i].base = NULL; //store a base city;
		arr[i].head = NULL; //store adjacent cities of the base city;
	}

}

//Deep copy
Graph::Graph(const Graph &g) {
	size = g.size;
	//if (g.arr) { //make sure dynamic array arr in g exist
	arr = new AdjList[size];
	for (int i = 0; i < size; i++) {
		arr[i] = g.arr[i]; //uses overloaded operator = in AdjList class

	}

	//}
}

Graph::~Graph() {
	delete[] arr;
}

int Graph::numOfCities() {
	int counter = 0;
	for (int i = 0; i < size; i++)
		if (arr[i].head != NULL)
			counter++;
	return counter;
}

set<int> Graph::findAdjCities(int baseID) const
{

	set<int> adjCityID; //to stores all adjacent cities' names of the city with baseName
	CityNode* root = arr[baseID].head; //root points to AdjList of base city
	while (root != NULL)
	{
		adjCityID.insert(root->ID); //stores one adj city in the set adjCity		
		root = root->next;
	} //now all adj cities of the base city is stored in set adjCity

	return adjCityID;
}

vector<int> Graph::shortestPath(int startID)
{

	//priority_queue< iPair, vector <iPair>, greater<iPair> > pq;
	priority_queue<iPair> pq;

	// Create a vector to store shortest path distances
	// initialize all  distances as infinite (INF)
	// For example, dist[0] the shortest path distance to NodeCity with ID 0
	vector<int> shortest(size, INF); //create V integers with value INF


	// Insert source itself in priority queue and initialize
	// its distance as 0.
	pq.push(std::make_pair(0, startID));
	shortest[startID] = 0;

	/* Looping till priority queue becomes empty (or all
	  distances are not finalized) */
	while (!pq.empty())
	{
		// The first vertex in pair is the minimum distance
		// vertex, extract it from priority queue.
		// vertex label is stored in second of pair (it
		// has to be done this way to keep the vertices
		// sorted distance (distance must be first item
		// in pair)
		//in pq, the second half of first pair, which is the node number
		int u = pq.top().second; //second is src in first looping
		pq.pop();

		// 'i' is used to get all adjacent vertices of a vertex
		//list< pair<int, int> >::iterator i;
		//root is used to get all adjacent node of a AdjList
		CityNode* root = arr[u].head;
		while (root != NULL) {
			int v = root->getID();
			int weight = root->getDistance();

			if (shortest[v] > shortest[u] + weight)
			{
				// Updating distance of v
				shortest[v] = shortest[u] + weight;
				pq.push(std::make_pair(shortest[v], v));
			}
			root = root->next;
		}

	}

	// Print shortest distances stored in dist[]
	//cout << "Start from city #" << startID << ":\n";
	//cout << "City ID\t   Distance from Source\n";
	//for (int i = 0; i < size; ++i)
	//cout << i << "\t" << shortest[i] << endl;

	return shortest;
}

int Graph::lowestPathPrice(int cityID, string pName) {

	vector<int> pathsToAll (shortestPath(cityID));
	//stores the shortest path distances from city #cityID to all cities in the graph


	vector<int> pathsToOwned;
	//will store the shortest path distances from city #cityID to cities owned by pName


	for (int i = 0; i < pathsToAll.size(); i++) {
		vector<string> v(arr[i].base->owners); //stores owners' names of city#i
		if (std::find(v.begin(), v.end(), pName) != v.end()) //if we find city#i is owned by pName
		{
			//cout << "found city #" << arr[i].base->getID() << "owned by " << pName << endl;
			pathsToOwned.push_back(pathsToAll[i]); //stores the distance to city#i in pathsToOwned
		}

	}

	//find the MINIMUM value in pathsToOwned.
	//then we can get the shortest path from city #cityID to a NEAREST city owned by pName

	if (pathsToOwned.size() == 0) //if pName does not own any city
		return 0;

	int min = pathsToOwned[0];

	for (int i = 1; i < pathsToOwned.size(); i++) {
		if (pathsToOwned[i] < min)
			min = pathsToOwned[i];
	}

	return min;

}

void createBaseCity(Graph *graph, map<string, int> myMap) { //map cannot be const
	CityNode *nptr;
	string name;
	int ID;

	//for each city's name in the map, find its find corresponding ID
	//create a city node with its ID
	//set its name according to ID
	//link this node to the a base according to its ID
	//e.g. if the ID is 0, then link this node to the base in arr[0], and so on	 
	for (map<string, int>::iterator it = myMap.begin(); it != myMap.end(); it++) {
		name = it->first; //city name is the first of the pair <"Montreal", 0>, that is, "Montreal"
		ID = myMap.at(name); // city ID is the corresponding integer of "Montreal", that is, 0
		nptr = new CityNode(ID);// create a city node with ID = 0;
		nptr->setName(name); // set the city name to "Montreal"
		graph->arr[ID].base = nptr; // add it to arr[0] in dyanamic array in graph
	}

}

void addEdge(Graph *graph, string firstCity, string secondCity, int distance, const map<string, int> myMap)
{
	//Add an edge from src to dest. A new node added to the adjacency list of src
	//node added at beginning
	int firstID, secondID;
	//cannot find scrName or destName in the map

	if (myMap.find(firstCity) == myMap.end() || myMap.find(secondCity) == myMap.end()) {
		cout << "At least one of the cities is not in the map! Edge cannot be created.";
		exit(1);
	}

	//find city Id according to its name
	else
	{
		firstID = myMap.at(firstCity);
		secondID = myMap.at(secondCity);
	}

	if ((firstID >= graph->size) || (secondID >= graph->size))
	{
		cout << "Invalid city ID.";
		exit(1);
	}

	//create a "destination" of first city (which is the second city)
	CityNode *nptr = new CityNode(secondID);

	//link the destination node to first city's AdjList(arr[scrID])
	nptr->setName(secondCity);

	nptr->setDistance(distance);//the second city is "distance" away from its base(first city base)
	nptr->next = graph->arr[firstID].head;
	graph->arr[firstID].head = nptr;

	//create a "destination" of second city (which is the first city)
	nptr = new CityNode(firstID);

	//link the "destination" node (source node) to second city's adjList
	nptr->setName(firstCity);
	nptr->setDistance(distance);
	nptr->next = graph->arr[secondID].head;
	graph->arr[secondID].head = nptr;
}


void printGraph(Graph* graph) {
	//loop over each adjacent list
	for (int i = 0; i < graph->size; i++) {

		CityNode *base = graph->arr[i].base;
		CityNode *root = graph->arr[i].head;
		cout << "Adjacency list of city " << base->ID << " " << base->name
			<< " (" << base->region
			<< ") Owned by :";
			
		for (int j = 0; j < graph->arr[i].base->owners.size(); j++) {
			cout << graph->arr[i].base->owners[j] << "  ";
		}
		cout << endl;
		while (root != NULL) {
			cout << "-> city ID: " << root->ID << ",\tcity name: " << root->name
				<< ",\t\tdistance to " << base->name << ": " << root->distance
				<< endl;
			root = root->next;
		}
		cout << endl;
	}
	cout << "----End of the map----\n";
}


void findConnected(Graph* graph, set<int>& visited, int beginCityID)
{
	//find all cities adjacent to base city
	set<int> adjCity = graph->findAdjCities(beginCityID);

	//of course, the begin city is part of the connected graph
	visited.insert(beginCityID);

	set<int>::iterator it;
	it = adjCity.begin(); //it points to the first adj city's name in the set

	//traverses the set of adjacent city names	
	while (it != adjCity.end())
	{
		//get one city name from the set
		int v = *it;

		//if this city is not visited, put it in the visited set
		if (visited.find(v) == visited.end())
		{
			visited.insert(v); //store this name to visited set			

			//the first connected city is the new base city in recursion
			findConnected(graph, visited, v);

		}
		it++;

	}
	//at this point, all conncected cities' names in the graph are stored in visited
}

bool isConnected(Graph* graph)
{
	set<int> connectedCity;
	int baseCityID = graph->arr[0].base->ID; //start traverse from first city

	//finds all connected cities, stores their names in connectedCity set
	findConnected(graph, connectedCity, baseCityID);

	cout << "Number of connected cities: " << connectedCity.size() << endl;
	cout << "Number of cities in the Map: " << graph->size << endl;

	//if the number of connected cities equals the number of cities in graph, returns true
	return (connectedCity.size() == graph->size);

}

bool isConnected2(Graph* graph, int beginCityID) {
	set<int> connectedCity;

	//start from beginCity
	//finds all connected cities, stores their names in connectedCity set
	findConnected(graph, connectedCity, beginCityID);

	cout << "Start from city #" << beginCityID
		<< ", number of connected cities: " << connectedCity.size() << endl;	
	
	return (connectedCity.size() == graph->numOfCities());
}

void removeEdge(Graph* graph, int cityID) {	
	CityNode* root;
	CityNode* prev;
	for (int i = 0; i < graph->size; i++) {
		if (graph->arr[i].base->getID() == cityID) {
			//cout << cityID << " found in base " <<  endl;;
			prev = graph->arr[i].head;
			root = graph->arr[i].head;
			graph->arr[i].head = NULL;  //disconnect the Adjlist head from all its node

			//deal with the node in heap
			while (root != NULL) {
				root = root->getNext(); // move to next node
				delete prev; //delete the node before root 
				prev = root; //points to root again
			}
			delete root; //delete the last node
			prev = NULL; //deal with dangling pointer
			root = NULL;
		}	
	}
}

void removeEdge2(Graph* graph, int cityID) {
	CityNode* root;
	CityNode* prev;
	for (int i = 0; i < graph->size; i++) {
		root = graph->arr[i].head; //points to the first node in AdjList		
		
		prev = graph->arr[i].head;//points to the same place as root at start
	
		

		//if cityName is in the head node
		if (root != NULL && root->getID() == cityID) { //we add root != NULL because arr[i]could be an empty Adjlist
										//because we might have already removed all city #i's adjacent cities in arr[i]
			//cout << cityName << " found in node list head " <<  endl;
			graph->arr[i].head = root->getNext();
			delete root;
			continue; //check next AdjList
		}		
		
		//else
		if (root != NULL) { //we add root != NULL because arr[i]could be an empty Adjlist
							//because we might have already  removed all city #i's adjacent cities in arr[i]
			
			root = root->next; //now prev points to the node before root
			while (root != NULL) {

				//if this is the node we want to delete				
				if (root->ID == cityID) {					
					//cout << cityID << " found in node list (not head) " <<  endl;
					prev->next = root->next; //say we want to delete node A, 
											 //this makes the node before A link to node after A					
					root->next = NULL; //make node A link to NULL					
					delete root; // delete node A
					root = NULL; // deal with dangling pointer (can also end while loop)
					
				}
				//else, check next node
				if (root != NULL)
					root = root->next;	
				else 
					break; //if root == NULL, it means cityName is deleted and dangling pointer is treated
				prev = prev->next;
				
			}
		}		
	}
}

/**/
void removeArea(Graph* graph, int areaNo) {
	int startID = (areaNo - 1) * 7;  //the ID of first city in area areaNo. First city in area 1 is the city 0.
	int endID = startID + 6; //last city in area 1 is city 6
	string cityName;
	for (int i = startID; i <= endID; i++) {
		removeEdge(graph, i); //remove all cities in this city's AdjList
		removeEdge2(graph, i); // remove this city from all other cities' Adjlist
	}
}
/**/



void mapLoader::Load() {
	cout << "Please input the name of the map file: \n";
	string fileName;
	cin >> fileName;
	ifstream inputStream;
	inputStream.open(fileName);

	if (inputStream.fail())
	{
		if (inputStream.fail())
		{
			cout << "Wrong format of map file!";
			exit(1);
		}
	}

	map<string, int> cityNameIDPair;
	int cityID = 0;
	string next;

	inputStream >> next; //read the first string in the file
	if (next != "[City]") //a map file should start with "[City]"
	{
		cout << "This is not a valid map file text!";
		exit(1);
	}

	//read the first part of the file (city name list)
	//stores them into map<string, int>
	while (!inputStream.eof()) {
		inputStream >> next;
		if (next == "[Edge]")
			break;
		//cout << next << endl;
		cityNameIDPair.insert(pair<string, int>(next, cityID));
		cityID++;  //after storing the last city, the city size still increment once
	}

	//read the second part of the text
	string firstCity;
	string secondCity;
	string distance;
	int intDistance;
	int size = cityID; //if there is 10 city, the cityID will be 10 now
	Graph gameMap(size);
	createBaseCity(&gameMap, cityNameIDPair);

	while (!inputStream.eof()) {
		inputStream >> firstCity >> secondCity >> distance;
		//cout << firstCity << " " << secondCity << " " << distance << endl;
		intDistance = std::stoi(distance); //cast string to int
		addEdge(&gameMap, firstCity, secondCity, intDistance, cityNameIDPair);
	}

	
	printGraph(&gameMap);

	if (isConnected(&gameMap))
		cout << "The original map is a connected graph.\n";
	else
		cout << "The original map is not a connected graph.\n";

	//Now will create a map for certain number of players
	//2 players -- 3 regions
	//3 players -- 3 regions
	//4 players -- 4 regions
	//5 players -- 5 regions
	//6 players -- 6 regions //in game rule it's 6 players -- 5 regions	
	

	int numOfplayer;
	int numToRemove; //how many areas to be removed
	int areaToRemove; // which area to be removed
	cout << "\nEnter the number of players (2-6): ";
	cin >> numOfplayer;
	while (numOfplayer < 2 || numOfplayer > 6) {
		cout << "Must be a number from 2-6. Enter again: ";
		cin >> numOfplayer;
	}

	switch (numOfplayer) {	
		case 2:
		case 3:
			numToRemove = 3;
			break;		
		case 4:
			numToRemove = 2;
			break;
		case 5:
			numToRemove = 1;
			break;
		case 6:
			numToRemove = 0;
			break;
	}
	cout << "In this game, there will be " << numOfplayer << " players.\n" 
		<< "You need to choose " << numToRemove << " area(s) you don't want (1 - 6).\n";
	
	Graph* copy;
	
	while (true) {
		copy = new Graph(gameMap);
		for (int i = 0; i < numToRemove; i++) {
			cout << "\nEnter the " << i << "th area you don't want: ";
			cin >> areaToRemove;
			removeArea(copy, areaToRemove);
		}
				
		
		printGraph(copy);

		int test = 0;
		for (int i = 0; i < copy->getSize(); i++) {
			if (copy->getArr()[i].getHead() == NULL)
				test++;
			else break;
		}
		


		cout << "The number of cities left in the map: " << copy->numOfCities() << endl;
		if (isConnected2(copy, test)) {
			cout << "\nAll areas in the map is connected. Good Luck in the game!\n";
			break;
		}
			
		else {
			cout << "\nNot all areas in the map is connected!! \nPlease choose the area you don't want again. \n";
			delete copy;
		}
	}

	

	/* Code to test if the copy is a deep copy, done *
	//add a new edge in the original graph
	addEdge(&gameMap, "Boston", "Buffalo", 100000, cityNameIDPair);
	//change one of the base in the original graph
	gameMap.arr[1].base->ID = 888;

	cout << "\n============= printing updated map ===================\n";
	printGraph(&gameMap); //will print a different graph

	cout << "\n============= printing copy of map ===================\n";
	printGraph(&copy); // will print a same graph with original graph (deep copy)
	/**/
	


	//Don't forget the destructor at the end
}