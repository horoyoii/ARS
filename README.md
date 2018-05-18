# Air/lineR/eserv/ati/onSyst/em
목표 : A/irline Rese/rvat/ion Sy/stem 

요인 : flight number, flight time, seat level, seat number, ticket price, travel time etc.

중점사항 : 
 1) modularity 
 2) the system should be integrated with UI.
 3) capacity to manage all the exception or error.

설계방안 :
## 1. Data Structure <br>

  가. Circular singly Linked List : this list is for the reservation table. 
    
    1) it should be up-to-date.
   
    2) it has its own ADT(Insert, Delete, Show etc) 
    
     
  나. Graph with Linked List : this graph is for the airline routes information.
  
     1) it contains all the path between every cities. 
     
     2) using this graph, we should extract the fast route by DFS and BFS algorithm.
     
     가) DFS 
       - It needs Stack.h.
        
     나) BFS
       - It needs CircularQueue.h
       
 ## 2. prerequisite <br>
    가. 15 cities (a ~ o) <br>
    나. 20 bidirectional routes<br>
    다. Maximum degree on each vertex : 4<br>
    라. The weight on routes : 100 - 1000km distances, 100 - 1000$ costs<br>
    
       
       
 ***
 제한사항
