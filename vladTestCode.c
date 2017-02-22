#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

typedef struct TreeNode{
	struct TreeNode *pLeftNode;
	struct TreeNode *pRightNode;
	int nodeValue;
}TreeNode;

typedef struct LinkedList{
	struct LinkedList *pNextNode;
	int value;
}LListNode;

typedef struct DLinkedList{
	struct DLinkedList *pNextNode;
	struct DLinkedList *pPrevNode;
	int    value;
}DLListNode;

LListNode *pListHead_1 = NULL;
LListNode *pListHead_2 = NULL;
TreeNode *pTreeRoot = NULL;

static int bTreeHeight = 0;
static int leftHight = 0;
static int rightHight = 0;
static int numberOfNodes = 0;

void invertList(LListNode **head);

/******************************************************************************************
*
* Function: partition
*
* This function assures that on the left side of an array all values are less than
* provided reference value, and that on the right side all values are bigger
*
*
*
*
*******************************************************************************************/
int partition (int a[], int l, int r)
{

	int i, j = r;
	int v = a[r];
	int temp;


	for(i = 0; i < 10; i++){
		printf("\na[%d] is %d", i, a[i]);
	}

	i = l - 1 ;
	for(;;){

		while (a[i] < v){
			i++;
		}

		while(a[--j] > v) {	
			if(l == j) break;
		}

		if(i >=j) break;

		temp = a[i];
		a[i] = a[j];
		a[j] = temp;
		
	}

	temp = a[i];
	a[i] = a[r];
	a[r] = temp;
 
	return i;
}


/******************************************************************************************
*
* Function: InsertInTree
*
*
*
*
*
*
*******************************************************************************************/
int insertInTree(TreeNode *pRoot, TreeNode *pNode){
	
	if(!pRoot){
		return 0;
	}
	if(!pNode){
		printf("\nInvalid Node!\n");
		return -1;
	}
	if(pRoot->nodeValue == pNode->nodeValue) return -1;

	if(pRoot->nodeValue > pNode->nodeValue){
		if(pRoot->pLeftNode){
			if(-1 == insertInTree(pRoot->pLeftNode, pNode)){
				return -1;
			}
		}
		else pRoot->pLeftNode = pNode;
	}
	else if (pRoot->nodeValue < pNode->nodeValue){
		if(pRoot->pRightNode){
			if (-1 == insertInTree(pRoot->pRightNode, pNode)){
				return -1;
			}
		}
		else pRoot->pRightNode = pNode;
	}
	return 0;
}


/******************************************************************************************
*
* Function: TraverseTree
*
*
*
*
*
*
*******************************************************************************************/

void traverseTree(TreeNode *pRoot, int *pTreeHight){

	if(pRoot->pLeftNode){
		traverseTree(pRoot->pLeftNode, &bTreeHeight);
	}
	
	if (pRoot->pRightNode){
		traverseTree(pRoot->pRightNode, &bTreeHeight);
	}
	if((pRoot->pLeftNode) || (pRoot->pRightNode)){
		(*pTreeHight)++;
	}
	numberOfNodes++;
}

/******************************************************************************************
*
* Function:treeHeight
*
*
*
*
*
*
*******************************************************************************************/

int treeHeight(TreeNode *pRoot){
	int u =0, v = 0;

	if(!pRoot) 
		return(-1);
	
	u = treeHeight(pRoot->pLeftNode);

	v = treeHeight(pRoot->pRightNode);

	
	if(u > v) 
		return (u+1); 
	else    
		return (v+1);

}

/******************************************************************************************
*
* Function: displayTree
*
*
*
*
*
*
*******************************************************************************************/

void displayTree(TreeNode *root){

	if(!root) return;
	displayTree(root->pRightNode);
	displayTree(root->pLeftNode);
	printf("\nThe tree node is %d\n", root->nodeValue);
	return;
}

/******************************************************************************************
*
* Function: vladTestCode
*
*
*
*
*
*
*******************************************************************************************/

void vladTestCode(int nodeValue)
{
   TreeNode *pTempNode = NULL;

   pTempNode = (TreeNode *)malloc(sizeof(TreeNode));
   pTempNode->pLeftNode = NULL;
   pTempNode->pRightNode = NULL;
   pTempNode->nodeValue = nodeValue;

   if (pTreeRoot == NULL){
	   pTreeRoot = pTempNode;	
   }else{
	   if (-1 == insertInTree(pTreeRoot, pTempNode)){
		   free(pTempNode);
	   }
   }

 //Test Inserting and printing out a btree
  // displayTree(pTreeRoot);
}


/******************************************************************************************
*
* Function: emptyTree
*
*
*
*
*
*
*******************************************************************************************/

void emptyTree(TreeNode *pRoot){
	if(!pRoot) return;
	emptyTree(pRoot->pLeftNode);
	emptyTree(pRoot->pRightNode);
	free(pRoot);
}

/******************************************************************************
*
* Function: testCodeForTree
*
*
*
*
*
*
******************************************************************************/

void testCodeForTree(){
	int h = 0;
#if 1	
	vladTestCode(2);
	vladTestCode(10);
	vladTestCode(17);
	vladTestCode(3);
	vladTestCode(8);
	vladTestCode(1);
	vladTestCode(4);
	vladTestCode(13);
	vladTestCode(1);
	vladTestCode(8);
#endif
#if 0
	vladTestCode(23);
	vladTestCode(90);
	vladTestCode(45);
	vladTestCode(80);
	vladTestCode(63);
	vladTestCode(75);
#endif
	
	displayTree(pTreeRoot);
	
	if(pTreeRoot){
		
		if(pTreeRoot->pLeftNode){
			traverseTree(pTreeRoot, &bTreeHeight);

		}
		else if(pTreeRoot->pRightNode)
			traverseTree(pTreeRoot, &bTreeHeight);
	    
		else{
			rightHight = leftHight = 1;
		}
	}
	
	printf("\nThe tree depth is %d\n", bTreeHeight);

	printf("\nNumber of nodes in the tree is %d\n", numberOfNodes);

	h = treeHeight(pTreeRoot);
	printf("\nThe tree depth BASED ON SEDGEWICK is %d\n", h);

	emptyTree(pTreeRoot);
	return;
}


/******************************************************************************
*
* Function: insertAtTheEndOfList
*
*
*
*
*
*
******************************************************************************/

LListNode * insertAtTheEndOfList(LListNode **head, int elementValue){

	LListNode *pNewNode = (LListNode *)malloc(sizeof(LListNode));
	LListNode *temp = NULL;

	pNewNode->value = elementValue;
	pNewNode->pNextNode = NULL;

	if(!(*head))
		*head = pNewNode;
	else{
		temp = *head;
		while(temp){
			if(temp->pNextNode)
				temp = temp->pNextNode;
			else{
				temp->pNextNode = pNewNode;
				break;
			}
		}
	}
	return pNewNode;
}

/******************************************************************************
*
* Function: displayList
*
*
*
*
*
*
******************************************************************************/

void displayList(LListNode *head){
	LListNode *temp = head;

	if(!head) printf("\nLIST is empty\n");
	
	while(temp){
		printf("\nLL NODE Element %d\n",temp->value);
		temp = temp->pNextNode;
	}

}

/******************************************************************************
*
* Function: displayDLList
*
*
*
*
*
*
******************************************************************************/

void displayDLList(DLListNode *head){
	DLListNode *temp = head;

	if(!head) printf("\nLIST is empty\n");
	
	while(temp){
		printf("\nDLL NODE Element %d\n",temp->value);
		temp = temp->pNextNode;
	}

}

/******************************************************************************************
*
* Function: sortList
*
* Description: Sort singly linked list using bubble sort for lins
*
*
*
*
*
*******************************************************************************************/

LListNode * sortList(LListNode **head){
	LListNode *tempBegin = NULL;
	LListNode *tempEnd = NULL;
	LListNode *next = NULL;
	LListNode *prev = NULL;
	int count = 1;
	int tempVal = 0;
	int i = 0, j = 0;

	if(!(*head))
		return tempBegin;
	tempBegin = *head;

	while(tempBegin->pNextNode){
		count++;
		tempBegin = tempBegin->pNextNode;
	}
	
	tempEnd = *head;
    invertList(&tempEnd);
	*head = tempEnd;

	for(i = 1; i < count; i++){
		for(j = count; i < j; j-- ){
			if((tempEnd)&&(tempEnd->pNextNode)&&(tempEnd->value > tempEnd->pNextNode->value)){
              //swap them
				//tempVal = tempEnd->value;
				//tempEnd->value = tempEnd->pNextNode->value;
				//tempEnd->pNextNode->value = tempVal;
				if(tempEnd->pNextNode->pNextNode)
					next = tempEnd->pNextNode->pNextNode;
				else
					next = NULL;

				tempEnd->pNextNode->pNextNode = tempEnd;

				//Check if we are at the begining of the Linked List
				//If not do this:
				if(prev){
					if(tempEnd->pNextNode)
						prev->pNextNode = tempEnd->pNextNode;
					//Adjust new previous pointer value
					prev = tempEnd->pNextNode;
				}
				//Else assign LList head to the new first node
				else{
					prev = tempEnd->pNextNode;
					*head = prev;
				}

				tempEnd->pNextNode = next;

			}else{
				prev = tempEnd;
				if(tempEnd && tempEnd->pNextNode)
					tempEnd = tempEnd->pNextNode;
				else tempEnd = NULL;
			}
		}
		tempEnd = *head;
	}

	return *head;
}

/******************************************************************************************
*
* Function: mergeLists
*
*
*
*
*
*
*******************************************************************************************/

LListNode * mergeLists(LListNode *head1, LListNode *head2){

	LListNode *temp1 = head1;
	LListNode *temp2 = head2;
	LListNode *mergedList = NULL;

	while(temp1 && temp2){
		while(temp1 && (temp1->value < temp2->value)){
			insertAtTheEndOfList(&mergedList, temp1->value);
			temp1 = temp1->pNextNode;
		}
		if(!(temp1->value == temp2->value))
			insertAtTheEndOfList(&mergedList,temp2->value);	
		temp2 =temp2->pNextNode;
	}
	
	while(temp2){
		insertAtTheEndOfList(&mergedList,temp2->value);		
		temp2 =temp2->pNextNode;
	}

	while(temp1){
		insertAtTheEndOfList(&mergedList,temp1->value);		
		temp1 =temp1->pNextNode;
	}
	return(mergedList);

}


/******************************************************************************************
*
* Function: invertList
*
* Inverts singly linked list
*
*
*
*
*******************************************************************************************/

void invertList(LListNode **head){
	LListNode *current = NULL;
	LListNode *prev = NULL;
	LListNode *next = NULL;

	current = *head;

	while(current){
		next = current->pNextNode;
		current->pNextNode = prev;
		prev = current;
		current = next;
	}
	*head = prev;
}


/******************************************************************************************
*
* Function: inverDLList
*
* Inverts Double Linked List
*
*
*
*
*******************************************************************************************/

void invertDLList(DLListNode **head){
   DLListNode *current = NULL;
   DLListNode *previous = NULL;
   DLListNode *next = NULL;

   current = *head;
   
   while(current){
	   next = current->pNextNode;
	   current->pNextNode = current->pPrevNode;
	   current->pPrevNode = current->pNextNode;
	   previous = current;
	   current = next;
   }
   *head = previous;
}

/******************************************************************************************
*
* Function: insertAtTheEndOfDLList
*
*
*
*
*
*
*******************************************************************************************/

DLListNode * insertAtTheEndOfDLList(DLListNode **head, int elementValue){

	DLListNode *pNewNode = (DLListNode *)malloc(sizeof(DLListNode));
	DLListNode *temp = NULL;

	pNewNode->value = elementValue;
	pNewNode->pNextNode = NULL;
	pNewNode->pPrevNode = NULL;

	if(!(*head)){
		*head = pNewNode;
	}
	else{
		temp = *head;
		while(temp){
			if(temp->pNextNode)
				temp = temp->pNextNode;
			else{
				temp->pNextNode = pNewNode;
				pNewNode->pPrevNode = temp;
				break;
			}
		}
	}
	return pNewNode;
}


/******************************************************************************************
*
* Function: freeList
*
* Frees memory allocated for a list
*
*
*
*
*******************************************************************************************/

void freeList(LListNode **head){
	LListNode *temp = NULL;
	LListNode *current = NULL;
	current = temp = *head;
	
	while(temp){
		current = temp;
		temp = temp->pNextNode;
		free(current);
	}
	*head = NULL;

}


/******************************************************************************
*
* Function: main
*
* Main test routine
*
*
*
*
******************************************************************************/

void main(){
	
	LListNode *llNode = NULL;
	LListNode *pMergedList = NULL;
    DLListNode *dllHead = NULL;
	int a[10], i = 0;

	testCodeForTree();

	llNode = insertAtTheEndOfList(&pListHead_1, 3);
	llNode = insertAtTheEndOfList(&pListHead_1, 6);
	llNode = insertAtTheEndOfList(&pListHead_1, 7);
	llNode = insertAtTheEndOfList(&pListHead_1, 1);
	llNode = insertAtTheEndOfList(&pListHead_1, 4);
	displayList(pListHead_1);

	invertList(&pListHead_1);
	
	displayList(pListHead_1);
	
	freeList(&pListHead_1);
	
	displayList(pListHead_1);

	printf("\n\n\n\n");
#if 1
	llNode = insertAtTheEndOfList(&pListHead_1, 3);
	llNode = insertAtTheEndOfList(&pListHead_1, 6);
	llNode = insertAtTheEndOfList(&pListHead_1, 7);
	llNode = insertAtTheEndOfList(&pListHead_1, 11);
	llNode = insertAtTheEndOfList(&pListHead_1, 14);
#endif

#if 1
	llNode = insertAtTheEndOfList(&pListHead_2, 4);
	llNode = insertAtTheEndOfList(&pListHead_2, 5);
	llNode = insertAtTheEndOfList(&pListHead_2, 8);
	llNode = insertAtTheEndOfList(&pListHead_2, 9);
	llNode = insertAtTheEndOfList(&pListHead_2, 13);
#endif

#if 0
	llNode = insertAtTheEndOfList(&pListHead_2, 3);
	llNode = insertAtTheEndOfList(&pListHead_2, 6);
	llNode = insertAtTheEndOfList(&pListHead_2, 7);
	llNode = insertAtTheEndOfList(&pListHead_2, 11);
	llNode = insertAtTheEndOfList(&pListHead_2, 14);
#endif

	pMergedList = mergeLists(pListHead_1, pListHead_2);
	printf("\nFirst List is");
	displayList(pListHead_1);
	printf("\n\nSecond List is\n");
	displayList(pListHead_2);

	printf("\nMerged List is");
	displayList(pMergedList);
	freeList(&pListHead_1);
	freeList(&pListHead_2);
	freeList(&pMergedList);

	printf("\n\n\nTest for Linked List Sort\n");
	llNode = insertAtTheEndOfList(&pListHead_1, 14);
	llNode = insertAtTheEndOfList(&pListHead_1, 7);
	llNode = insertAtTheEndOfList(&pListHead_1, 6);
	llNode = insertAtTheEndOfList(&pListHead_1, 3);
	llNode = insertAtTheEndOfList(&pListHead_1, 15);
	displayList(pListHead_1);
	
	sortList(&pListHead_1);
	printf("\n\n\nAfter Sorting Linked List \n");
	displayList(pListHead_1);

	printf("\n\n\nSecond unsorted Linked List\n");
	llNode = insertAtTheEndOfList(&pListHead_2, 9);
	llNode = insertAtTheEndOfList(&pListHead_2, 13);
	llNode = insertAtTheEndOfList(&pListHead_2, 8);
	llNode = insertAtTheEndOfList(&pListHead_2, 4);
	llNode = insertAtTheEndOfList(&pListHead_2, 5);
	displayList(pListHead_2);
	sortList(&pListHead_2);
	printf("\n\n\nAfter Sorting the Second Linked List \n");
	displayList(pListHead_2);

	printf("\n---------------------------------------------\n");
	pMergedList = mergeLists(pListHead_1, pListHead_2);
	printf("\nMerged List is\n");
	displayList(pMergedList);
	freeList(&pListHead_1);
	freeList(&pListHead_2);
	freeList(&pMergedList);


	insertAtTheEndOfDLList(&dllHead, 3);
	insertAtTheEndOfDLList(&dllHead, 6);
	insertAtTheEndOfDLList(&dllHead, 7);
	insertAtTheEndOfDLList(&dllHead, 1);
	insertAtTheEndOfDLList(&dllHead, 4);
	displayDLList(dllHead);
	invertDLList(&dllHead);
	displayDLList(dllHead);
	freeList((LListNode **)&dllHead);


	rand();

	for (i = 0; i < 10; i++){
		a[i] = rand() % 10;
		printf("\na[%d] is %d", i, a[i]);
	}
	partition(a, 1, 9);

	printf("\n\nAfter Sorting:\n");
	for (i = 0; i < 10; i++){
		printf("\na[%d] is %d", i, a[i]);
	}
}
