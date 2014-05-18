#include <vector>
#include <queue>
#include <set>
using namespace std;
class vertex_silver;
typedef vector<vertex_silver*>::iterator vit;

struct path
{
	vertex_silver*			p1;
	vertex_silver*			p2;
	vector< vertex_silver* >	elements;	
	int				unvisited_count;
	int				unvisited_count2();
	void			visit_all( vector<set<path*> >& vx_to_path_map );
};

typedef set<vertex_silver*>::iterator sit;
class vertex_silver
{
private:
	int _label;
	bool _visited;
	set< vertex_silver* > _adjacency; // Does not check duplicates..
public:
	vertex_silver( int label );
	~vertex_silver();
	int label()				{ return _label; }
	void add( vertex_silver* v);

	void set_visited( bool val ){ _visited = val; }
	bool is_visited()		{ return _visited; }

	// For traversals..
	sit adj_begin()			{ return _adjacency.begin(); }
	sit adj_end()			{ return _adjacency.end(); }

	vertex_silver* parent;	// optionally store this values for some algos.
};

class graph_silver
{
private:
	vector<vertex_silver*> _adj_matrix;
	int _max;
public:
	graph_silver();
	void add_edge( int, int );
	void add_vertex_silver( int );
	void unvisit_all();
	int  size() { return _max + 1; }
	vertex_silver* vertex_silver_at( int a )
		{ return _adj_matrix[a]; }
	~graph_silver();

	 template <typename T>
		void simple_BFS( int start, T& x );
	
	template <typename T>
		void path_BFS( int start, T& x );
		
};

template <typename T>
void graph_silver::simple_BFS( int start, T& x )
{
	vertex_silver* v = vertex_silver_at( start );
	queue< vertex_silver* > Q;
	Q.push( v );

	while( !Q.empty() )
	{
		v = Q.front();
		v->set_visited( true ); // Dont go back as this is parent..
		
		for( sit it = v->adj_begin(); it != v->adj_end(); it++ )
		{
			if( !(*it)->is_visited() )
				Q.push( *it );
		}		

		Q.pop();
		x( v ); // Do what the user wants with this vertex_silver;
	}
	
}


template <typename T>
void graph_silver::path_BFS( int start, T& x )
{
	vertex_silver* v = vertex_silver_at( start );
	queue< vertex_silver* > Q;
	Q.push( v );

	while( !Q.empty() )
	{
		v = Q.front();
		v->set_visited( true ); // Dont go back as this is parent..
		
		for( sit it = v->adj_begin(); it != v->adj_end(); it++ )
		{
			if( !(*it)->is_visited() )
			{
				(*it)->parent = v;				
				Q.push( *it );
			}			
		}		

		Q.pop();
		x( v ); // User logic on this vertex_silver;
	}
	unvisit_all();
}

vertex_silver::vertex_silver( int label )
	: _label( label ), _visited( false ), parent( NULL )
{
}

vertex_silver::~vertex_silver()
{
	_adjacency.clear();
}

void vertex_silver::add( vertex_silver* v )
{ 
	if( v != this )
		_adjacency.insert( v ); 
}

void graph_silver::add_vertex_silver( int v )
{
	// Increase size of graph_silver if beyond current size...
	if( v > _max )
	{
		for(; _max != v; _max++ ) // Add till label..
			_adj_matrix.push_back( NULL );
	}
	
	// Add new if not already present..
	if( !_adj_matrix[ v ] ) 
		_adj_matrix[ v ] = new vertex_silver( v );
}
void graph_silver::add_edge( int v1, int v2 )
{
	add_vertex_silver( v1 );
	add_vertex_silver( v2 );

	_adj_matrix[ v1 ]->add( vertex_silver_at( v2 ) );
	_adj_matrix[ v2 ]->add( vertex_silver_at( v1 ) );
}

graph_silver::graph_silver()
	: _max( -1 )
{
}

graph_silver::~graph_silver()
{
	// Delete each vertex_silver;
	for( vit it = _adj_matrix.begin(); it != _adj_matrix.end(); it++ )
		delete *it;

	// clear the leftovers...
	_adj_matrix.clear();
}


void path::visit_all( vector<set<path*> >& vx_to_path_map )
{
	//p1->set_visited( true );
	//p2->set_visited( true );

	elements.push_back( p1 );
	elements.push_back( p2 );

	for( vit it = elements.begin(); 
		it != elements.end() ; it ++ )
	{
		if( (*it)->is_visited() ) continue;
		(*it)->set_visited( true );

		set<path*> path_set = vx_to_path_map[ (*it)->label() ];
		for( set<path*>::iterator pit =  path_set.begin(); 
			pit != path_set.end(); pit ++ )
		{
			(*pit)->unvisited_count--;
		}				
	}
}

//int path::unvisited_count2()
//{
//	int count = 0;
//	if( !p1->is_visited() ) count++;
//	if( !p2->is_visited() ) count++;
//
//	for( vector<vertex_silver*>::iterator it = elements.begin(); 
//		it != elements.end() ; it ++ )
//		if( !(*it)->is_visited() )
//			count ++;
//
//	return count;
//}


void graph_silver::unvisit_all()
{
	for( vit it = _adj_matrix.begin(); it != _adj_matrix.end(); it++ )
		(*it)->set_visited( false );
}
// COmparison operator..
struct maximum
{
	bool operator()( path* l, path* r )
	{
		int unvisits = l->unvisited_count;
		int unvisits2 = r->unvisited_count;
		//int unvisits2 = (*it)->unvisited_count2();
		if( unvisits < unvisits2 )
		{
			return true; 
		}
		else if( unvisits == unvisits2 )
		{
			return l->p2->label() > r->p2->label(); // r label is less..
		}
		else
			return false; // l is greater..
	}
}path_comp;

struct path_creator
{
	vector<path*> _paths;
	void operator()( vertex_silver* v )
	{
		// If this is an end node...
		if( ( v->parent ) && (++v->adj_begin()) == v->adj_end() )
		{			
			path* new_path = new path();	
			new_path->unvisited_count = 0;
			new_path->unvisited_count++;
			new_path->p2 =  v ;
			v = v->parent;
			while( v->parent )
			{
				new_path->elements.push_back( v );
				new_path->unvisited_count++;
				v = v->parent;
			}
			new_path->p1 = v;
			new_path->unvisited_count++;
			_paths.push_back( new_path );
		}
	}
}pathObj;

void fill_vertex_silver_to_path_map( vector<set<path*> > &vertex_silver_to_path_map, vector<path*> paths )
{
	for( vector<path*>::iterator pit = paths.begin(); pit != paths.end(); pit++ )
	{
		path* p = *pit;
		vertex_silver_to_path_map[ p->p1->label() ].insert( p ); //p1 in p
		vertex_silver_to_path_map[ p->p2->label() ].insert( p ); //p2 in p

		for( vit it = p->elements.begin(); it != p->elements.end(); it ++ )
		{
			vertex_silver_to_path_map[ (*it)->label() ].insert( p ); // all elements in p.
		}
	}
}

vector<int> solution_silver( int K, vector<int> &T )
{
	graph_silver G;										// Build the graph_silver
	for( int i = 0; i < (int)T.size(); i++ )
		G.add_edge( i, T[i] );

	G.path_BFS<path_creator>( K , pathObj );		// Get paths from K to all ends..

	vector<set<path*> > vertex_silver_to_path_map( G.size() ); // Create a map that keeps a track of
	fill_vertex_silver_to_path_map( vertex_silver_to_path_map, pathObj._paths );// all paths in which this vx is

	vector<int> result;
	result.push_back( K );
	
	while( !pathObj._paths.empty() )
	{
		make_heap( pathObj._paths.begin(), pathObj._paths.end(), path_comp );
		path* top_path  = *pathObj._paths.begin();
		result.push_back( top_path->p2->label() );	// Destinations

		std::pop_heap (pathObj._paths.begin(),pathObj._paths.end(), path_comp); 
		pathObj._paths.pop_back();
		top_path->visit_all( vertex_silver_to_path_map );	// Mark this path visited.		
	}
	
	return result;
}