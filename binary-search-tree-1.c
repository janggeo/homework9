/*[2021076029] [장정환]
	수정사항
	1)freeBST(Node* head)에서 if(head->left == head)를 if(head->right == head)로 변경
		initializeBST함수에서 root노드를 가리키는 head를 초기화 할때 오른쪽 자식이 head노드를 가리키도록 초기화 하였다. 
	
	2)처음 root노드를 추가할때 initializeBST함수를 먼저 호출 하지 않고 바로 insert할 수 있도록 main 함수에서 
		head포인터 동적할당
	
	3)deleteLeafNode(Node* head, int key) 함수에서 입력받은 key값을 가지는 node를 지울때
		해당하는 key값을 가지는 노드가 없을 경우 오류 메시지 출력하도록 수정
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node{	//노드 구조체
	int key;
	struct node* left;	//왼쪽 자식
	struct node* right;	//오른쪽 자식
}Node;

int initializeBST(Node** h);			//이진트리 초기화

void inorderTraversal(Node* ptr);		//recursive inorder traversal
void preorderTraversal(Node* ptr);		//recursive preorder traversal
void postorderTraversal(Node* ptr);		//recursive postorder traversal
int insert(Node* head, int key);		//insert a node to the tree
int deleteLeafNode(Node* head, int key);	//delete the leaf node for the key
Node* searchRecursive(Node* ptr, int key);	//search the node for the key
Node* searchIterative(Node* head, int key);	//search the node for the key
int freeBST(Node* head);	//free all memories allocated to the tree


int main(void)
{
	printf("-----[2021076029] [장정환]-----");
	char command;
	int key;

	Node* head = (Node*)malloc(sizeof(Node));
	head->key=-9999;
	head->left=NULL;
	head->right=head;

	Node* ptr = NULL;	/*temp*/

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");
		
		printf("Command = ");
		scanf(" %c",&command);

		switch (command)
		{
		case 'z': case 'Z':
			initializeBST(&head);	//tree 초기화
			break;
		case 'q': case 'Q':
			freeBST(head);			//트리에 할당된 메모리 free
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d",&key);
			insert(head,key);		//입력받은 key를 가지는 노드 트리에 추가
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d",&key);
			deleteLeafNode(head, key);	//단말노드 제거
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);	//iterative 방식으로 search
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n",ptr->key, ptr);
			else
			printf("\n Cannot find the node [%d]\n",key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d",&key);
			ptr=searchRecursive(head->left, key);	//recursive 방식으로 search
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n",ptr ->key, ptr);
			else
			printf("\n Cannot find the node [%d]\n", key);
			break;
		case 'i': case 'I':
			inorderTraversal(head->left);		//중위순회
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);		//전위순회
			break;
		case 't': case 'T':
			postorderTraversal(head->left);		//후위순회
			break;
		default:
			printf("\n		>>>>>  Concentration!!  <<<<<		\n");
			break;
		}
	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h){ //head포인터의 값을 변경하기 위해 더블포인터를 매개변수로 선언
	/* 이진트리가 비어있지 않은경우, 트리에 할당된 노드들 해제*/
	if(*h != NULL)
		freeBST(*h);

	/*head node를 다시 만든다*/
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left=NULL;	/*root*/
	(*h)->right= *h;
	(*h)->key = -9999;
	return 1;
}

int insert(Node* head, int key)
{	/*새로운 노드 할당 및 초기화*/
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key=key;
	newNode->left=NULL;
	newNode->right=NULL;

	if(head->left==NULL){	//root 노드가 비어있을 경우
		head->left=newNode;	//새로운 노드를 루트노드로 지정
		return 1;
	}
	/*head->left is the root*/
	Node* ptr = head->left;
	/*입력받은 새로운 노드의 부모를 가리킬 포인터*/
	Node* parentNode =NULL;

	while(ptr !=NULL){
		/*입력받은 key 값이 트리에 이미 존재할경우*/
		if(ptr->key == key) return 1;

		/*부모노드밑에 새로운 노드를 추가해야하므로 부모노드를 계속 추적해야한다*/
		parentNode = ptr;

		/*입력받은 key 값이 ptr이 가리키는 노드의 key값 보다 클경우
			ptr을 오른쪽 노드로 이동, 다른경우 왼쪽으로 이동*/
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}
	/*부모노드에 연결*/
	if(parentNode->key >key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;

}

void inorderTraversal(Node* ptr)
{	/*재귀호출로 중위 순회*/
	if(ptr){
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)
{	/*재귀호출로 전위 순회*/
	if(ptr){
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)
{	/*재귀호출로 후위 순회*/
	if(ptr){
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ",ptr ->key);
	}
}

int deleteLeafNode(Node* head, int key)
{
	if (head == NULL){
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL){
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/*head-> left is the root */
	Node* ptr = head->left;
	Node* parentNode=head;
	while(ptr != NULL){

		if(ptr->key == key){
			if(ptr->left==NULL && ptr->right ==NULL){	//ptr이 단말노드인경우
				/*root노드만 존재할 경우*/
				if(parentNode==head)
					head->left=NULL;	//가리키는 값을 NULL로 변경
				/*왼쪽 노드와 오른쪽 노드를 제거할경우*/
				if(parentNode->left==ptr)
					parentNode->left=NULL;
				else
					parentNode->right=NULL;
				free(ptr);
			}
			else{
				printf("the node [%d] is not a leaf \n",ptr->key);
			}
			return 1;
		}
		/*ptr의 부모를 가리킬 포인터*/
		parentNode= ptr;

		/*입력받은 key 값이 ptr이 가리키는 노드의 key값 보다 클경우
			ptr을 오른쪽 노드로 이동, 다른경우 왼쪽으로 이동*/
		if(ptr->key <key)
			ptr=ptr->right;
		else
			ptr= ptr->left;
	}
	printf("[%d] is not in tree\n",key);
	return -1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL)	//노드가 비었을경우
		return NULL;
	
	if(ptr->key < key)
		ptr = searchRecursive(ptr->right, key);	//오른쪽 자식을 재귀호출
	else if(ptr->key > key)
		ptr=searchRecursive(ptr->left, key);	//왼쪽 자식을 재귀호출
	/*if ptr->key ==key*/
	return ptr;
}

Node* searchIterative(Node* head, int key)
{
	Node* ptr = head->left;	//root 노드

	while(ptr != NULL)
	{
		if(ptr->key == key)
			return ptr;	//key 값이 존재할경우 해당되는 주소를 반환
		/*입력받은 key값이 더 클 경우 ptr을 오른쪽 자식으로 이동
			작은 경우 왼쪽으로 이동*/
		if(ptr->key < key)
			ptr=ptr->right;
		else	
			ptr = ptr->left;
	}

	return NULL;	//해당되는 key값이 없는경우 NULL 반환
}

void freeNode(Node* ptr)
{
	if(ptr){	//recursive 방식으로 노드 해제
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);	//root 노드 해제
	}
}

int freeBST(Node* head)
{
	if(head->right == head)	//root 노드를 가리키는 head노드만 존재할경우
	{
		free(head);
		return 1;
	}

	Node* p = head->left;	//root

	freeNode(p);	//tree 동적할당 해제

	free(head);	//root 노드를 가리키는 노드 동적할당 해제
	return 1;
}
