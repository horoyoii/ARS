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
    
 ## 3. Modularity <br>
    1)  Graph with Linked List
      - Graph.h 
        - gLinkedList.h
        - gStack.h
    

***
1. 모든 경로 탐색


2. 탐색된 모든 경로에 대한 각각의 경로의 cost 계산

 A-B-C로 연결되어있다면  
int HowMuch(int A, int B); 안에는
정점 간 cost가 적힌 2차원 배열이 정의되어 있고
return arr[A][B]을 한다.
이를 A-B, B-C 두번 반복하여 나온 cost의 합을 반환한다.
 ***
 제한사항
