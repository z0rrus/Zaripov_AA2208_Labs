#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

class Node {
public:
    int frequency;
    char value;
    Node* left, * right;

    Node(int freq, char val) {
        frequency = freq;
        value = val;
        left = nullptr;
        right = nullptr;
    }
};

struct compare {
    bool operator()(Node* left, Node* right) {
        return (left->frequency > right->frequency);
    }
};

Node* build_huffman_tree(string data) {
    unordered_map<char, int> frequencies;
    for (char& c : data) {
        frequencies[c]++;
    }

    priority_queue<Node*, vector<Node*>, compare> heap;
    for (auto& p : frequencies) {
        Node* n = new Node(p.second, p.first);
        heap.push(n);
    }

    while (heap.size() > 1) {
        Node* node1 = heap.top();
        heap.pop();
        Node* node2 = heap.top();
        heap.pop();

        Node* merged = new Node(node1->frequency + node2->frequency, '\0');
        merged->left = node1;
        merged->right = node2;

        heap.push(merged);
    }

    return heap.top();
}

void build_code_table(Node* root, unordered_map<char, string>& code_table, string code) {
    if (root->value) {
        code_table[root->value] = code;
    }
    else {
        build_code_table(root->left, code_table, code + "0");
        build_code_table(root->right, code_table, code + "1");
    }
}

string compress_data(string data) {
    Node* root = build_huffman_tree(data);
    unordered_map<char, string> code_table;
    build_code_table(root, code_table, "");

    string encoded_data = "";
    for (char& c : data) {
        encoded_data += code_table[c];
    }

    return encoded_data;
}

string decompress_data(string encoded_data, Node* root) {
    Node* current_node = root;
    string decoded_data = "";

    for (char& bit : encoded_data) {
        if (bit == '0') {
            current_node = current_node->left;
        }
        else {
            current_node = current_node->right;
        }

        if (current_node->value) {
            decoded_data += current_node->value;
            current_node = root;
        }
    }

    return decoded_data;
}

int main() {
    string data = "example data for compression";
    string encoded_data = compress_data(data);
    cout << "Encoded data: " << encoded_data << endl;

    Node* root = build_huffman_tree(data);
    string decoded_data = decompress_data(encoded_data, root);
    cout << "Decoded data: " << decoded_data << endl;

    return 0;
}
