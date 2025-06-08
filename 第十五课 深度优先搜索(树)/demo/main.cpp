#include <iostream>
#include <vector>
#include <stack>


struct Node {
    char data;
    std::vector<Node*> children;    
};

Node* build_tree_A() {
    Node* root = new Node();
    root->data = 'A';
    root->children.push_back(new Node());
    root->children[0]->data = 'B';
    root->children.push_back(new Node());
    root->children[1]->data = 'C';
    root->children.push_back(new Node());
    root->children[2]->data = 'D';

    Node* childB = root->children[0];
    childB->children.push_back(new Node());
    childB->children[0]->data = 'E';
    childB->children.push_back(new Node());
    childB->children[1]->data = 'F';
    childB->children.push_back(new Node());
    childB->children[2]->data = 'G';
      
    return root;
}

Node * build_binary_tree(){
    Node * root = new Node();
    root->data = 'A';
    root->children.push_back(new Node());
    root->children[0]->data = 'B';
    root->children.push_back(new Node());
    root->children[1]->data = 'C';

    Node * childB = root->children[0];
    childB->children.push_back(new Node());
    childB->children[0]->data = 'D';
    childB->children.push_back(new Node());
    childB->children[1]->data = 'E';

    Node * childC = root->children[1];
    childC->children.push_back(new Node());
    childC->children[0]->data = 'F';
    childC->children.push_back(new Node());
    childC->children[1]->data = 'G';

    return root;
}




void dfs(Node* root,  char target = 'F') { 
    if (root == nullptr) return;

    std::stack<Node*> stack;
    stack.push(root);
    while (!stack.empty()) {
        Node* current = stack.top();
        stack.pop();

        std::cout << current->data << " ";

        if (current->data == target) {
            std::cout << "Found: " << target << std::endl;
            return;
        }

        for (int i = current->children.size() - 1; i >= 0; --i) {
            stack.push(current->children[i]);
        }
    }   
    std::cout << "Not Found: " << target << std::endl;
    return;    
}

void deep_first_traversal(Node* root) {
    if (root == nullptr) return;

    std::vector<char> result;
    std::stack<Node*> stack;
    stack.push(root);
    while (!stack.empty()) {
        Node* current = stack.top();
        stack.pop();
        result.push_back(current->data);

        for (int i = current->children.size() - 1; i >= 0; --i) {
            stack.push(current->children[i]);
        }
    }
    
    std::cout << "result:" << std::endl;
    for (char c : result) {
        std::cout << c << " ";
    }   
    std::cout << std::endl;
       
}


void root_left_right(Node* root){
    if (root == nullptr) return;

    if (root->children.size() > 2) {      
        std::cout << "Error: More than two children for node " << root->data << std::endl;  
        return;
    }
    std::cout << root->data << " ";
    if (root->children.size() > 0) {
        root_left_right(root->children[0]);
    }

    if (root->children.size() > 1) {
        root_left_right(root->children[1]);
    }   

}




int main(void){

    Node* general_tree_root = build_tree_A();
    std::cout << "DFS in General Tree: " << std::endl;
    dfs(general_tree_root, 'F');

    Node* binary_tree_root = build_binary_tree();
    std::cout << "DFS in Binary Tree: " << std::endl;
    dfs(binary_tree_root, 'F');


    deep_first_traversal(binary_tree_root);

    std::cout << "Root-Left-Right Traversal: " << std::endl;
    root_left_right(binary_tree_root);
    std::cout << std::endl;




    return 0;
}