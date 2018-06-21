# Airline Reservation System
목표 : Airline Reservation System 

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
   1)  Graph with Linked List <br>
    - Graph.h <br>
        - gLinkedList.h [Graph 구현용 LinkedLIst ADT] <br>
        - gStack.h      [DFS 구현용 Stack ADT ] <br>
        - SelectRotues.h [DFS로 탐색된 모든 경로를 묶어서 반환하는 LinkedList ADT] <br>
        - 탐색된 경로는 1차원 배열에 순차적으로 저장된다.  <br>
    - Weight Graph <br>
        - 간선 간에 가중치를 부여한다. 가중치를 가지는 2차원 배열 정의<br>
        - 이를 통하여 경로 간에 cost와 distance 계산 <br>
    

 ## 4. DFS Implement
    1) DFS로 탐색을 진행하되, 도착지점을 찾은 경우  <br>
      - 저장되어있는 스택의 값들을(시작지점-도착지점 간의 경로) Route_Node에 저장한다. <br>
    2) 이후 백트래킹으로 모든 경우의 경로를 탐색한다. <br>
    3) 모든 경로 탐색 완료 시 종료한다. <br>
    4) 반환값 : 시작지점-도착지점 간의 모든 경로가 저장된 노드들이 이어진 Route_head 가 반환된다. <br>
    5) Route_head를 대상으로 Display 및 Select의 기능을 제공한다. <br>


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
