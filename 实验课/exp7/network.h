#ifndef NETWORK
#define NETWORK

#include <map>
#include <list>
#include <queue>
#include <limits>

using namespace std;

//template<class vertex, class Compare = less<vertex> >
template<class vertex>
class network
{
		//node in the adjacency list, a to-vetex, an associated weight
        struct vertex_weight_pair
        {
            vertex to;
            double weight;

            // Postcondition: this vertex_weight_pair has been initialized
            //                from x and y.
            vertex_weight_pair (const vertex& x, const double& y)
            {
                to = x;
                weight = y;
            } // two-parameter constructor

            // Postcondition: true has been returned if this
            //                vertex_weight_pair is less than x.
            //                Otherwise, false has been returned.
            bool operator> (const vertex_weight_pair& p) const
            {
                return weight > p.weight;
            } // operator>

        }; // class vertex_weight_pair

        typedef typename std::list<vertex_weight_pair> adj_list; //adjacency list
        typedef typename adj_list::iterator adj_list_itr; //adjacency list iterotor
		typedef typename std::map<vertex, adj_list> ver_adj_map; //map each vetex to its adjacency list
        typedef typename ver_adj_map::iterator ver_adj_map_itr;

    protected:
        ver_adj_map ver_adj; //vertex - adjacency list map

    public:

		// Postcondition: this network is empty.
		network() { }

		// Postcondition: the number of vertices in this network has been
		//                returned.
		unsigned int size()
		{
			return ver_adj.size();
		} // method size


		// Postcondition: true has been returned if this network contains no
		//                vertices.  Otherwise, false has been returned.
		bool empty()
		{
			return size() == 0;
		} // method empty


		// Postcondition: true has been returned if this network contains the
		//                edge <v1, v2>.  Otherwise, false has been returned.
		bool contains_edge(const vertex& v1, const vertex& v2)
		{
			ver_adj_map_itr itr = ver_adj.find(v1);
			if (itr == ver_adj.end() || ver_adj.find(v2) == ver_adj.end()) //not both exist
				return false;

			adj_list_itr list_itr;

			for (list_itr = ((*itr).second).begin(); //itr points to a pair in ver_adj_map: first:vertex, second:adj_list
					list_itr != ((*itr).second).end();
						list_itr++)
				if ((*list_itr).to == v2) //vertex-weight-struct
					return true;
			return false;
		} // method contains_edge


		// Postcondition: if v is already in this network, false has been
		//                returned. Otherwise, the map with v and an empty list
		//                has been added to this network and true has been
		//                returned.
		bool insert_vertex(const vertex& v)
		{
			return ver_adj.insert(
				pair<vertex, list<vertex_weight_pair> > //map stores pair type
				(v, list<vertex_weight_pair>()) //empty list
			).second; //map insert returns pair<iterator,bool> 
															
		} // method insert_vertex


		// Postcondition: if the edge <v1, v2> is already in this network false
		//                has been returned. Otherwise, that edge with the
		//                given weight has been inserted in this network and
		//                true has been returned.
		bool insert_edge(const vertex& v1, const vertex& v2, const double& weight)
		{
			if (contains_edge(v1, v2))
				return false;
			insert_vertex(v1); //may already exist
			insert_vertex(v2); //may already exist
			(*(ver_adj.find(v1))).second.push_back(vertex_weight_pair(v2, weight));
			return true;
		} // method insert_edge

		/*=======================================DIJKSTRA'S ALGORITHM==========================================================*/
        // Postcondition: the shortest path from v1 to v2 and its total weight
        //                have been returned; if such a path is found,
		//				  returns the list of vertices on the shortest path
		//				  and the total weight of the shortest path;
		//				  otherwise, returns an empty list and the value -1.0
       
        pair<list<vertex>, double> get_shortest_path (const vertex& v1, const vertex& v2)
        {
            // 如果顶点不存在，直接返回
            if (ver_adj.find(v1) == ver_adj.end() || ver_adj.find(v2) == ver_adj.end())
                return make_pair(list<vertex>(), -1.0);

            // 距离与前驱记录
            map<vertex, double> dist;
            map<vertex, vertex> prev;
            const double INF = std::numeric_limits<double>::infinity();

            // 初始化
            for (auto &m : ver_adj)
            {
                dist[m.first] = INF;
            }
            dist[v1] = 0.0;

            // 优先队列（最小堆）
            auto cmp = [&](const vertex &a, const vertex &b){
                return dist[a] > dist[b];
            };
            priority_queue<vertex, vector<vertex>, decltype(cmp)> pq(cmp);
            pq.push(v1);

            // Dijkstra
            while (!pq.empty())
            {
                vertex u = pq.top();
                pq.pop();

                if (u == v2) break; // 找到目标

                // 遍历邻居
                for (auto &edge : ver_adj[u])
                {
                    vertex w = edge.to;
                    double cost = edge.weight;
                    if (dist[u] + cost < dist[w])
                    {
                        dist[w] = dist[u] + cost;
                        prev[w] = u;
                        pq.push(w);
                    }
                }
            }

            // 构建路径
            if (dist[v2] == INF)
                return make_pair(list<vertex>(), -1.0);

            list<vertex> path;
            for (vertex at = v2; at != v1; at = prev[at])
                path.push_front(at);
            path.push_front(v1);

            return make_pair(path, dist[v2]);
        }
}; // class network

#endif