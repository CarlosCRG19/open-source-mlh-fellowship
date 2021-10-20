#include <bits/stdc++.h>

using namespace std;

struct Node {
    public:
        char data;
        int priority;

        Node *left, *right;

        Node(char data, int priority) {
            this->data = data;
            this->priority = priority;
        }
};

struct compare {
    bool operator()(Node *left, Node *right) {
        return (left->priority > right->priority);
    }
};

void printCodeword(Node* rootNode, string prefix) {

    if(!rootNode) return;

    if(rootNode->data != '#') cout << rootNode->data << ": " << prefix << "\n";

    printCodeword(rootNode->left, prefix + "0");
    printCodeword(rootNode->right, prefix + "1");


}

void huffmanCoding(map<char, int> charDistribution){
    
    struct Node *left, *right, *top;

    priority_queue<Node*, vector<Node*>, compare> priorityQueue;

    for(auto &pair: charDistribution){
        priorityQueue.push(new Node(pair.first, pair.second));
    }

    while (priorityQueue.size() != 1) {
        
        left = priorityQueue.top();
        priorityQueue.pop();

        right = priorityQueue.top();
        priorityQueue.pop();

        top = new Node('#', left->priority + right->priority);
        top->left = left;
        top->right = right;

        priorityQueue.push(top);
    }

    printCodeword(priorityQueue.top(), "");


}

int main() {

    string text;
    cin >> text;

    map<char,int> ocurrencies; 

    for(int i = 0; i < text.length(); i++) {
        if(ocurrencies.find(text[i]) == ocurrencies.end()) {
            ocurrencies.insert(make_pair(text[i],1));
        } else {
            ocurrencies.at(text[i]) += 1;
        }
    }

    huffmanCoding(ocurrencies);

}