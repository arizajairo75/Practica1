#pragma once
#include <vector>
#include <string>

struct AVLNode {
    std::string word;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(const std::string& w) : word(w), left(nullptr), right(nullptr), height(1) {}
};

int height(AVLNode* n) {
    return n ? n->height : 0;
}

int balanceFactor(AVLNode* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

void updateHeight(AVLNode* n) {
    if (n) n->height = 1 + std::max(height(n->left), height(n->right));
}

// Rotación simple a la derecha (caso LL)
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x  = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left  = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

// Rotación simple a la izquierda (caso RR)
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y  = x->right;
    AVLNode* T2 = y->left;
    y->left  = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

AVLNode* insert(AVLNode* node, const std::string& word) {
    // 1. Inserción normal de BST
    if (!node) return new AVLNode(word);
    if (word < node->word)      node->left  = insert(node->left,  word);
    else if (word > node->word) node->right = insert(node->right, word);
    else return node; // duplicado, ignorar

    // 2. Actualizar altura
    updateHeight(node);

    // 3. Verificar balance y rotar si es necesario
    int bf = balanceFactor(node);

    // Caso LL
    if (bf > 1 && word < node->left->word)
        return rotateRight(node);
    // Caso RR
    if (bf < -1 && word > node->right->word)
        return rotateLeft(node);
    // Caso LR
    if (bf > 1 && word > node->left->word) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    // Caso RL
    if (bf < -1 && word < node->right->word) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Inorder: izquierda → raíz → derecha = orden alfabético
void inorder(AVLNode* node, std::vector<std::string>& result) {
    if (!node) return;
    inorder(node->left,  result);
    result.push_back(node->word);
    inorder(node->right, result);
}

// Liberar memoria del árbol
void deleteTree(AVLNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}