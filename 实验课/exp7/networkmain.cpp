#include <iostream>
#include <string>
#include "network.h"

using namespace std;

int main()
{
    const string SENTINEL = "***";

    const string PROMPT =
        "Please enter two vertices and a weight; the sentinel is ";

    const string SHORTEST_PATH_MESSAGE =
        "\n\n\nThe shortest path and its total weight are\n\n";

    string v1, v2;

    double weight;

    network<string> my_network; //vertex type is string; string compare is default for storing

    cout << PROMPT << SENTINEL << endl;
    cin >> v1;
    while (v1 != SENTINEL)
    {
        cin >> v2 >> weight;
        my_network.insert_edge (v1, v2, weight);
        cout << PROMPT << SENTINEL << endl;
        cin >> v1;
    } // getting edges

    string start, finish;

    cout << "\nPlease enter start and finish vertices" << endl;
    cin >> start >> finish;
	cout << endl;

	pair<list<string>, double> result = my_network.get_shortest_path(start, finish);
	list<string>::iterator vertex_list_itr;

    if (result.first.empty() == true)
        cout << "Path does not exist!" << endl;
    else
    {
        for (vertex_list_itr = result.first.begin();
            vertex_list_itr != result.first.end();
            vertex_list_itr++)
            cout << *vertex_list_itr << endl;
        cout << endl << "End of shortest path from " << start << " to " << finish << endl;
        cout << "Path weight = " << result.second << endl;
    }

    return 0;
}