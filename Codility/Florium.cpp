#include <vector>
#include <queue>
#include <list>
#include <algorithm>
using namespace std;
class vertex;
typedef vector<vertex*>::iterator vit;
typedef vector<vertex*>::reverse_iterator rvit;
typedef list<vertex*>::iterator lit;
typedef list<vertex*>::reverse_iterator rlit;

class vertex
{
private:
	int _label;
	bool _visited;
	list< vertex* > _adjacency; // Does not check duplicates..
public:
	vertex( int label );
	~vertex();
	int label()				{ return _label; }
	void add( vertex* v);
	void remove( vertex* v );
	void remove( lit it );

	void set_visited( bool val ){ _visited = val; }
	bool is_visited()		{ return _visited; }
	
	int branches;
	int distance;
	int weight;
	vertex* destination;
	bool is_destination;

	// For traversals..
	lit adj_begin()			{ return _adjacency.begin(); }
	lit adj_end()			{ return _adjacency.end(); }
	rlit adj_rbegin()		{ return _adjacency.rbegin(); }
	rlit adj_rend()			{ return _adjacency.rend(); }

	int count()				{ return (int)_adjacency.size(); }
	vertex* parent;	// optionally store this values for some algos.

	bool operator<(vertex& v) { return _label < v._label; };
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
	void merge_vertex( vertex* v );
	void merge_vertex( lit it );

	void unvisit_all();
	void reset();
	int  size() { return _max + 1; }
	vertex* vertex_at( int a )
		{ return _adj_matrix[a]; }
	void fill_dest_to_cost( list< pair<int,int> >& );
	void simplify_graph( int K );
	~graph();

	bool is_cyclic( int K);
	template <typename T>
		void path_BFS( int start, T& x );
	
	// Do logic for x.
	template <typename T>
		void simple_BFS( int start, T& x );

};

void graph::merge_vertex( vertex* v )
{
	vertex* v1 = *(v->adj_begin());
	vertex* v2 = *(++v->adj_begin());		

	v1->remove( v );
	v2->remove( v );

	v1->add( v2 );
	v2->add( v1 );

	if( v2->distance > v1->distance )
	{
		v2->weight += v->weight;
		v2->parent = v1;
	}
	else
	{
		v1->weight += v->weight;	
		v1->parent = v2;
	}

	v->weight = -1; // Flagging this useless..
}

void graph::merge_vertex( lit it )
{
	vertex* v1 = *((*it)->adj_begin());
	vertex* v2 = *(++(*it)->adj_begin());		

	v1->remove( it );
	v2->remove( it );

	v1->add( v2 );
	v2->add( v1 );

	if( v2->distance > v1->distance )
	{
		v2->weight += (*it)->weight;
		v2->parent = v1;
	}
	else
	{
		v1->weight += (*it)->weight;	
		v1->parent = v2;
	}

	(*it)->weight = -1; // Flagging this useless..
}

void graph::simplify_graph( int K)
{
	vertex* k = vertex_at( K );
	for( vit it = _adj_matrix.begin(); it != _adj_matrix.end(); it++ )
	{
		if( ((*it) != k) && (*it)->count() == 2  )
		{
			merge_vertex( *it );
		}
	}
}

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
		for( rlit it = v->adj_rbegin(); it != v->adj_rend(); it++ )
		{
			if( !(*it)->is_visited() )
			{
				(*it)->distance = v->distance + 1;
				(*it)->parent = v;		// Parent for path creation and return...		
				v->branches++;			// Increment the branches..
				Q.push( *it );			// Push for BFS..
			}			
		}	
		Q.pop();
		x( v ); // Do logic..
	}
}

struct empty{
	void operator() ( vertex* v )
	{
	}
}empt;

bool graph::is_cyclic( int K )
{
	simple_BFS( K, empt );
	unvisit_all();
	vertex* v = vertex_at( K );
	queue< vertex* > Q;
	Q.push( v );

	while( !Q.empty() )
	{
		v = Q.front();
		v->set_visited( true ); // Dont go back as this is parent..
		for( rlit it = v->adj_rbegin(); it != v->adj_rend(); it++ )
		{
			if( (*it)->is_visited() && ((*it) != v->parent))
				return true;
			else if( (*it) != v->parent )
				Q.push( *it );			// Push for BFS..		
		}	
		Q.pop();
	}
	return false;
}

void graph::fill_dest_to_cost( list< pair<int,int> >& map )
{
	for( rvit it = _adj_matrix.rbegin(); it != _adj_matrix.rend(); it++ )
	{
		if( !(*it)->is_destination ) continue;
		map.push_back( pair<int,int>( (*it)->label(), (*it)->distance ) );		
	}
}

vertex::vertex( int label )
	: _label( label ), weight( 1 ), _visited( false ), parent( NULL ), branches( NULL ), distance( NULL ), destination( NULL ), is_destination( false )
{
}

vertex::~vertex()
{
	_adjacency.clear();
}

void vertex::add( vertex* v )
{ 
	if( v != this )
		_adjacency.push_back( v ); 
}

void vertex::remove( vertex* v )
{ 
	if( v != this )
		_adjacency.erase( find( _adjacency.begin(), _adjacency.end(), v ) ); 
}

void vertex::remove( lit it )
{
	if( *it != this )
		_adjacency.erase( it );
}

void graph::add_vertex( int v )
{
	// Increase size of graph if beyond current size...
	if( v > _max )
	{
		for(; _max != v; _max++ ) // Add till label..
			_adj_matrix.push_back( NULL );
	}
	
	// Add new if not already present..
	if( !_adj_matrix[ v ] ) 
		_adj_matrix[ v ] = new vertex( v );
}
void graph::add_edge( int v1, int v2 )
{
	add_vertex( v1 );
	add_vertex( v2 );

	_adj_matrix[ v1 ]->add( vertex_at( v2 ) );
	_adj_matrix[ v2 ]->add( vertex_at( v1 ) );
}

graph::graph()
	: _max( -1 )
{
}

graph::~graph()
{
	// Delete each vertex;
	for( vit it = _adj_matrix.begin(); it != _adj_matrix.end(); it++ )
		delete *it;

	// clear the leftovers...
	_adj_matrix.clear();
}


void graph::unvisit_all()
{
	for( vit it = _adj_matrix.begin(); it != _adj_matrix.end(); it++ )
		(*it)->set_visited( false );
}

void graph::reset()
{
	for( vit it = _adj_matrix.begin(); it != _adj_matrix.end(); it++ )
	{
		(*it)->set_visited( false );
		(*it)->parent = NULL;
		(*it)->distance = 0;
		(*it)->weight = 1;
		(*it)->is_destination = false;
		(*it)->branches = 0;
	}
}

void fill_results( vector<int>& result , list< pair<int,int> >& dest_to_cost )
{
	list< pair<int,int> >::iterator it_next;
	for( list< pair<int,int> >::iterator it = dest_to_cost.begin();
		 !dest_to_cost.empty() ;)
	{
		it_next = ++it;
		it--;

		if( (*it).second == 1 )
		{
			result.push_back( (*it).first );			
			dest_to_cost.erase( it );
		}
		else			
			(*it).second --;
		
		if( it_next == dest_to_cost.end() )
			it = dest_to_cost.begin();
		else
			it = it_next;
	}
}

struct JunctionSolver
{
	vector< vertex* > _junctions;
	vertex* K;
	void operator()( vertex*& v )
	{
		if( (v->count() > 2) || (v->label() == K->label())  )
			_junctions.push_back( v );
	}
	
	void solve( graph& G );
	void set_destination( lit it, vertex* junc);
	JunctionSolver( vertex* v ) : K( v ) {}
};

void JunctionSolver::set_destination( lit it, vertex* junc)
{
	vertex* v = *it;
	v->is_destination = true;
	v->distance -= junc->distance;
	junc->remove( it );
	junc->branches--;
}

void JunctionSolver::solve( graph& G )
{
	while( !_junctions.empty() )
	{
		vertex* junc = _junctions.back();

		vertex* max_v = NULL;
		lit max_it;

		// One pass to find the max vertex at this junction...
		for( lit it = junc->adj_begin(); it != junc->adj_end();  )
		{			
			if( *it == junc->parent ) 
			{
				it++;
				continue; //dont go back..
			}			

			if( max_v == NULL ){ 
				max_v = *it;
				max_it = it;
				it++;
				continue;
			}

			vertex* v = *it;
			lit it2 = ++it;
			it--;

			if( v->weight > max_v->weight )
			{
				set_destination( max_it, junc );
				max_v = v;
				max_it = it;
			}
			else if( (v->weight == max_v->weight) && (v->label() < max_v->label() ) )
			{
				set_destination( max_it, junc );
				max_v = v;
				max_it = it;
			}
			else
			{
				set_destination( it, junc );
			}
			it = it2;
		}
		
		
		// Keep the graph simplified.. if it is not the last junction...
		while( (max_v->parent != K)  && max_v->parent->branches == 1 )
				G.merge_vertex( max_v->parent );
		
		if( max_v->parent == K && (K->branches == 1))
		{
			max_v->is_destination = true;
			max_v->distance = max_v->weight + 1;		
		}
		
		_junctions.pop_back();
	}
}

bool is_valid_graph( vector<int> &T, int K)
{
	graph G;										// Build the graph
	for( int i = 0; i < (int)T.size(); i++ )
		G.add_edge( i, T[i] );

	if( G.is_cyclic( K ) ) return false;
	return true;
}
vector<int> solution( int K, vector<int> &T )
{
	if( 1 == (int)T.size() )
		return T;

	graph G;										// Build the graph
	for( int i = 0; i < (int)T.size(); i++ )
		G.add_edge( i, T[i] );

	JunctionSolver junctions( G.vertex_at( K ) );
	G.simple_BFS< JunctionSolver >( K, junctions ); // Collect all junctions.. mark distances, branches etc.
	
	G.simplify_graph( K );
	junctions.solve( G); // find actual distance for each vertex.. the number of unvisited in that path...
	
	list< pair<int, int> > dest_to_cost;
	G.fill_dest_to_cost( dest_to_cost ); // Turn problem into start graph..
	
	vector<int> result;
	fill_results( result, dest_to_cost ); // Fill the result as per problem statement..

	result.push_back( K );
	
	reverse( result.begin(), result.end() );
	return result;
}