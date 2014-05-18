#include "Graph.h"

vertex::vertex( int label )
	: _label( label ), _visited( false )
{
}

vertex::~vertex()
{
	_adjacency.clear();
	delete _path;
}

void vertex::add( vertex* v )
{ 
	if( v != this )
		_adjacency.push_back( v ); 
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


int path::unvisited_count()
{
	int count = 0;
	if( !p1->is_visited() ) count++;
	if( !p2->is_visited() ) count++;

	for( set<vertex*>::iterator it = elements.begin(); 
		it != elements.end() ; it ++ )
		if( !(*it)->is_visited() )
			count++;

	return count;
}

void path::visit_all()
{
	p1->set_visited( true );
	p2->set_visited( true );

	for( set<vertex*>::iterator it = elements.begin(); 
		it != elements.end() ; it ++ )
			(*it)->set_visited( true );
}

void graph::unvisit_all()
{
	for( vit it = _adj_matrix.begin(); it != _adj_matrix.end(); it++ )
		(*it)->set_visited( false );
}