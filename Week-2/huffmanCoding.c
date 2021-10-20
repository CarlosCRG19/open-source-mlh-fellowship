#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


#define MAX_CHARS 128 // characters in ASCII table

struct Node{

    char data;
    int priority;
    
    struct Node *left, *right, *next;
    
};

// Function to create a new node
struct Node* newNode(char data, int priority) {
    struct Node *temp = (struct Node*) malloc(sizeof(struct Node));
    temp->data = data;
    temp->priority = priority;
    temp->left = NULL;
    temp->right = NULL;
    
    return temp;
}


//-- Priority Queue Implementation --//
int queue_size = 0;

int getLeftChildIndex(int parentIndex) {return 2*parentIndex + 1;}
int getRightChildIndex(int parentIndex) {return 2*parentIndex + 2;}
int getParentIndex(int childIndex) {return (childIndex - 1) / 2;}

int hasLeftChild(int index, int size) {return getLeftChildIndex(index) < size;}
int hasRightChild(int index, int size) {return getRightChildIndex(index) < size;}
int hasParent(int index) { return getParentIndex(index) >= 0; }

struct Node* leftChild(int index, struct Node *array[]) {return array[getLeftChildIndex(index)];}
struct Node* rightChild(int index, struct Node *array[]) {return array[getRightChildIndex(index)];}
struct Node* parent(int index, struct Node *array[]) {return array[getParentIndex(index)];}

void swap(struct Node **a, struct Node **b){
    struct Node *temp = (*b);
    *b = *a;
    *a = temp;
}

void heapifyDown(struct Node* array[]) {
    int index = 0;
    while(hasLeftChild(index, queue_size)){
        int smallerChildIndex = getLeftChildIndex(index);
        if(hasRightChild(index, queue_size) && leftChild(index, array)->priority > rightChild(index, array)->priority) {
            smallerChildIndex = getRightChildIndex(index);
        } 
        if(array[index]->priority < array[smallerChildIndex]->priority) {
            break;
        } else {
            swap(&array[index], &array[smallerChildIndex]);   
        }
        index = smallerChildIndex;
    }
}

void heapifyUp(struct Node* array[]) {
    int index = queue_size - 1;
    while(hasParent(index) && parent(index, array)->priority > array[index]->priority) {
        swap(&array[getParentIndex(index)], &array[index]);
        index = getParentIndex(index);
    }
}


void push(struct Node* array[], struct Node* newNode) {
    
    if(queue_size == 0){
        array[0] = newNode;
        queue_size += 1;
    } else {
        array[queue_size] = newNode;
        queue_size += 1;
        heapifyUp(array);
    }
}

void pop(struct Node* array[]){
    array[0] = array[queue_size-1];
    --queue_size;
    heapifyDown(array);
}


struct Node* top(struct Node* array[]) {
    return array[0];
}

// A utility function to print an array of size n
void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
 
    printf("\n");
}
 
// Utility function to check if this node is leaf
int isLeaf(struct Node* root)
 
{
 
    return !(root->left) && !(root->right);
}

void printCodes(struct Node* root, int arr[],
                int top)
 
{

    if (root->left) {
 
         arr[top] = 0;
         printCodes(root->left, arr, top + 1);
    }
 
    if (root->right) {
 
         arr[top] = 1;
         printCodes(root->right, arr, top + 1);
    }
 
    if (isLeaf(root)) {
 
         printf("%c: ", root->data);
         printArr(arr, top);
    }
}
 


//-- Huffman Coding Algorithm --//

void huffmanCoding(int n, char chars[], int freqs[]) {


    struct Node* queue_array[n], *root, *right, *left;


    for(int i=0; i<n; ++i){
        struct Node *temp = newNode(chars[i], freqs[i]);
        push(queue_array, temp);
    }


    while(queue_size != 1) {
        
        left = top(queue_array);
        pop(queue_array);

        right = top(queue_array);
        pop(queue_array);



        root = newNode('#', left->priority + right->priority);
        root->left = left;
        root->right = right;

        push(queue_array, root);

    }

    int bitArray[MAX_CHARS];

    printCodes(top(queue_array), bitArray, 0);

}

int main() {
    
    char message[MAX_CHARS];
    fgets(message, MAX_CHARS, stdin);
    
    // // Distribution table
    char characters[MAX_CHARS];
    int occurences[MAX_CHARS]; // this works as a map in c++, charactes[i] is a key and occurences[i] is a value

    int n, m, count, i=0;
    for(n=0; message[n]; n++){
        count = 1;
        for(m=n+1; message[m]; m++){
            if(message[n] == message[m]) {
                count++;
                message[m]='`';
            }
        }

        if(message[n] != '`'){
            characters[i] = message[n];
            occurences[i] = count;
            i++;   
        }
    }
 
    huffmanCoding(i-1, characters, occurences);

    return 0;
}