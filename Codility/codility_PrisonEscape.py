# you can use #print for debugging purposes, e.g.
#print "this is a debug message"
#([1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [0, 0, 0, 1, 2, 4, 2, 5, 5, 4], [1, 4])
#with WRONG ANSWER [ got 4 expected 3 ]

#([1, 2, 3, 4, 5, 6, 7, 8, 9, 10],[0, 1, 2, 0, 0, 5, 3, 0, 2, 6], [0, 6]).              
import Queue

gaurd_count = 0
graph = {}
parent = []
prisoners = [] 
killed = {}
def preprocess_graph( graph, C ):
    for i in graph:
        if i in C:
            continue
    
        value = graph[i]
        if len(value) == 2:
            #print "remove this 2 chain at :", i
            graph[ value[0] ].remove( i )
            graph[ value[1] ].remove( i )
            graph[ value[0] ].append( value[1] )
            graph[ value[1] ].append( value[0] )        
    pass

def processed( q, C ):
    # the normal BFS on this...
    global gaurd_count
    global killed
    
    if q.empty():
        #print "Q is empty"
        return False    
    item = q.get()   
    
    for i in graph.get( item ):
        #print "item:", item, "to : ", i         
        if parent[i] == parent[ item ]: #dont traverse back
            continue
        elif prisoners[i]: 
            #print "reached a prisoner at", i
	    gaurd_count += 1 
	    return False
    	#reached a point from a different search path
        elif (parent[i] != -1) and (parent[i] != parent[item]):
	    #print "Reached search path", parent[i]
	    continue
        else:
	    #print "Inserting to Q:", i
            q.put( i )
            parent[i] = parent[item]

    return True 
    
def solution(A, B, C):
    global gaurd_count
    global graph
    global prisoners
    global parent
    global killed
    graph.clear()
    del prisoners[:]
    del parent[:]
    killed.clear()

    print A, B, C
    if len( C ) == 0:
        return 0 
        
    # write your code in Python 2.7    
    for i in range( len(A) ):
        if graph.has_key( A[i] ):
            graph.get( A[i]).append( B[i] )           
        else:
            graph[ A[i] ] = [B[i]]
        
        if graph.has_key( B[i] ):
            graph.get( B[i] ).append( A[i] )
        else:
            graph[ B[i] ] = [A[i]]
    
    # remove unwanted linear chains.
    #preprocess_graph( graph, C ) 
    
    q_of_q = Queue.Queue()
    
    for i in range( len( graph.values() ) ):
        if( len( (graph.values())[i] ) == 1 ):
            q = Queue.Queue()
            q.put( i )
            q_of_q.put( q )  
            parent.append( i )
        else:
            parent.append( -1 )
        
        prisoners.append( False )          
        
    for i in range( len(C) ):
	if len( graph.get( C[i] ) ) == 1:
		return -1
	else:
        	prisoners[ C[i] ] = True
            
    gaurd_count = 0 
    #print "Qcount is:", q_of_q.qsize()
    #print parent
    #print prisoners
    
    while not q_of_q.empty():
        q = q_of_q.get()    
        if processed( q, C ):
            q_of_q.put( q )            
    
    return gaurd_count
