#include <vector>
#include <queue>
#include <set >
using namespace std;
class vertex;
typedef vector<vertex*>::iterator vit;

struct path
{
	vertex*			p1;
	vertex*			p2;
	set< vertex* >	elements;
	int unvisited_count();
	void visit_all();
};


class vertex
{
private:
	int _label;
	bool _visited;
	vector< vertex* > _adjacency; // Does not check duplicates..
public:
	vertex( int label );
	~vertex();
	int label()				{ return _label; }
	void add( vertex* v);

	void set_visited( bool val ){ _visited = val; }
	bool is_visited()		{ return _visited; }

	// For traversals..
	vit adj_begin()			{ return _adjacency.begin(); }
	vit adj_end()			{ return _adjacency.end(); }

	path* _path;		// optionally store this values for some algos.
};

class graph
{
private:
	vector<vertex*> _adj_matrix;
	int _max;
public:
	graph();
	void add_edge( int, int );
	void add_vertex( int );
	void unvisit_all();

	vertex* vertex_at( int a )
		{ return _adj_matrix[a]; }
	~graph();

	 template <typename T>
		void simple_BFS( int start, T& x );
	
	template <typename T>
		void path_BFS( int start, T& x );
		
};

template <typename T>
void graph::simple_BFS( int start, T& x )
{
	vertex* v = vertex_at( start );
	queue< vertex* > Q;
	Q.push( v );

	while( !Q.empty() )
	{
		v = Q.front();
		v->set_visited( true ); // Dont go back as this is parent..
		
		for( vit it = v->adj_begin(); it != v->adj_end(); it++ )
		{
			if( !(*it)->is_visited() )
				Q.push( *it );
		}		

		Q.pop();
		x( v ); // Do what the user wants with this vertex;
	}
	
}


template <typename T>
void graph::path_BFS( int start, T& x )
{
	vertex* v = vertex_at( start );
	v->_path = new path(); //Dummy path
	v->_path->p1 = v->_path->p2 = v;

	queue< vertex* > Q;
	Q.push( v );

	while( !Q.empty() )
	{
		v = Q.front();
		v->set_visited( true ); // Dont go back as this is parent..
		
		for( vit it = v->adj_begin(); it != v->adj_end(); it++ )
		{
			if( !(*it)->is_visited() )
			{
				x( (*it), v->_path ); // let the adjacent vertex know the current path.
				Q.push( *it );
			}			
		}		

		Q.pop();
	}
	
}