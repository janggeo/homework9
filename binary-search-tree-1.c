/*[2021076029] [장정환]

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int key;
	struct node* left;
	struct node* right;
}Node;

int initializeBST(Node** h);

void inorderTraversal(Node* ptr);
void preorderTraversal(Node* ptr);
void postorderTraversal(Node* ptr);
int insert(Node* head, int key);
int deleteLeafNode(Node* head, int key);
Node* searchRecursive(Node* ptr, int key);
Node* searchIterative(Node* head, int key);
int freeBST(Node* head);


int main(void)
{
	char command;
	int key;
	Node* head =NULL;
	Node* ptr = NULL;

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
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d",&key);
			insert(head,key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d",&key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n",ptr->key, ptr);
			else
			printf("\n Cannot find the node [%d]\n",key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d",&key);
			ptr=searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n",ptr ->key, ptr);
			else
			printf("\n Cannot find the node [%d]\n", key);
			break;
		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n		>>>>>  Concentration!!  <<<<<		\n");
			break;
		}
	}while(command != 'q' && command != 'Q');

	return 1;
}