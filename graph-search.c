/*
 * Graph Search
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 10

typedef struct Vertex{
	int data;
	struct Vertex *link;
} Vertex;

typedef struct Graph {
	Vertex *Head;
} Graph;

/* for stack */
#define MAX_STACK_SIZE		20 // 스택의 최대 크기를 20으로 저장
Vertex* stack[MAX_STACK_SIZE];
int top = -1;

Vertex* pop(); // 스택을 pop하는 함수
void push(Vertex* aNode); // 스텍에 push하는 함수

/* for queue */
#define MAX_QUEUE_SIZE		20 // 큐의 최대 크기를 20으로 저장
Vertex* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Vertex* deQueue(); // 큐에서 삭제하는 함수
void enQueue(Vertex* aNode); // 큐에 추가하는 함수

Graph* initialize(Graph *G);
int freeGraph(Graph *G);
int insertVertex(Graph *G, int v);
int insertEdge(Graph *G, int u, int v);
int DepthFS(Graph *G, int v);
int BreathFS(Graph *G, int v);
void printGraph(Graph *G);

int main()
{
	printf("[----- [Chaerin Jung] [2020039022] -----]");

	char command;
	int u, v;
	Graph* graph = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                         Graph Searches                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = z                                       \n");
		printf(" Insert Vertex        = v      Insert Edge                  = e \n");
		printf(" Depth First Search   = d      Breath First Search          = b \n");
		printf(" Print Graph          = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			graph = initialize(graph);
			break;
		case 'q': case 'Q':
			freeGraph(graph);
			break;
		case 'v': case 'V':
			printf("Your Num = ");
			scanf("%d", &v);
			insertVertex(graph, v);
			break;
		case 'd': case 'D':
			printf("Your Num = ");
			scanf("%d", &v);
			DepthFS(graph, v);
			break;
		case 'p': case 'P':
			printGraph(graph);
			break;
		case 'e': case 'E':
			printf("Your Num = ");
			scanf("%d %d", &u, &v);
			insertEdge(graph, u, v);
			insertEdge(graph, v, u);
			break;
		case 'b': case 'B':
			printf("Your Num = ");
			scanf("%d", &v);
			BreathFS(graph, v);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}
Graph* initialize(Graph *G)
{
	if(G != NULL) freeGraph(G);

	Graph *temp = (Vertex*)malloc(sizeof(Vertex));
	for(int i = 0; i < MAX_VERTEX; i++){
		temp[i].Head = NULL;
		//temp[i] = 0;
	}

	top = -1;
	front = rear = -1;

	return temp;
}

int freeGraph(Graph *G)
{
	Vertex* n;

	for(int i = 0; i < MAX_VERTEX; i++){
		n = G[i].Head;
		while(n != NULL){
			free(n);
			n = n->link;
		}
		if((G + i) != NULL) free(G[i].Head);
	}
	free(G);
}

int insertVertex(Graph *G, int v)
{
	Vertex *new = (Vertex*)malloc(sizeof(Vertex));
	new->data = v;
	new->link = NULL;

	if(G->Head != NULL){
		printf("The Vertex of [%d] already exists!!\n", v);
		return 0;
	}

	else if (v > MAX_VERTEX){
		printf("[%d] is out of range!!\n");
		return 0;
	}

	else{
		G->Head = new;
		return 0;
	}
}
int insertEdge(Graph *G, int u, int v)
{
	Vertex *new = (Vertex*)malloc(sizeof(Vertex));
	new->data = v;
	new->link = NULL;

	Vertex *n, *trail;
	n = G[u].Head;
	trail = n;

	if(u > MAX_VERTEX || v > MAX_VERTEX){
		printf("Vertex is out of range!!");
		return 0;
	}

	else if(G[u].Head == NULL || G[v].Head == NULL){
		printf("There is no such vertex..\n");
		return 0;
	}

	else
	{
		if (n->link == NULL) {
			n->link = new;
			return 0;
		}
		/* key를 기준으로 삽입할 위치를 찾는다 */
		while(n != NULL) {
			if(n->data >= v) {
				/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
				if(n == G[u].Head) {
					G[u].Head->link = new;
					new->link = n->link;
				} 
				else { /* 중간이거나 마지막인 경우 */
					new->link = n;
					trail->link = new;
				}
				return 0;
			}
			trail = n;
			n = n->link;
		}

		/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
		trail->link = new;
		return 0;
	}
}
int DepthFS(Graph *G, int v)
{}
int BreathFS(Graph *G, int v)
{}
void printGraph(Graph *G)
{
	int i = 0;
	Vertex *p, *n;
	p = G[i].Head;
	n = p->link;

	printf("\n---PRINT\n");

	if(G == NULL){
		printf("Nothing to print....\n");
		return;
	}

	while(i < MAX_VERTEX){
		if(p == NULL) p = G[++i].Head;

		else{
			printf("%d의 인접리스트", i);
			while(n != NULL){				
				printf("-> %d", n->data);
				n = n->link;
			}
			printf("\n");
			i++;
			p = G[i].Head;
		}
	}
}

Vertex* pop()
{
	Vertex *p; // node를 가리키는 포인터 p 생성

	if(top == -1) return NULL; // stack이 비어있으면 바로 종료
	else p = stack[top--]; // 그렇지 않으면 p에 스택의 top 값을 받고 top의 값을 하나 감소시킴

	return p; // p반환
}

void push(Vertex* v)
{
	stack[++top] = v; // 스택의 top을 하나 증가시키면서 해당 값 저장
}

Vertex* deQueue()
{
	if (front == rear){
		return NULL; // 큐가 비어있으면 바로 종료
	}
	front = (front + 1) % MAX_QUEUE_SIZE; // front의 다음 인덱스 값을 저장
	return queue[front]; // 해당 인덱스의 큐 값 반환
}

void enQueue(Vertex* aNode)
{
	if (((rear+1)%MAX_QUEUE_SIZE) == front) { // rear의 다음 값이 front일 경우 즉, 큐가 포화상태일 경우
		printf(" There is an error!! (queue is full)"); // 오류 문자열 출력
		return;
	}
	rear = (rear + 1) % MAX_QUEUE_SIZE; // rear의 값을 한 칸 증가시킴
	queue[rear] = aNode; // 증가시킨 rear에 해당하는 큐에 저장
}