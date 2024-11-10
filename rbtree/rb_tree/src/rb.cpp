#include "trees/rb.hpp"
#include <iostream>


namespace trees {

RB::RB():root(nullptr) {
	// TODO Auto-generated constructor stub
}

void RB::balance(RBNode* node) {
    std::cout << "Entering balance for node " << (node ? std::to_string(node->getData()) : "nullptr") << std::endl;
    root->setColor(BLACK);
    // Asegurarse de que el nodo no es la raíz y su padre es rojo
    while (node != root && node->getParent() && node->getParent()->getColor() == 'R') {
        RBNode* parent = node->getParent();
		if (parent == root) {
            break;
        }
        RBNode* grandparent = parent->getParent();
        
        if (parent == grandparent->getLeft()) { // Caso en el que el padre está a la izquierda del abuelo
            RBNode* uncle = grandparent->getRight();
            
            if (uncle && uncle->getColor() == 'R') { // Caso 2: tío rojo
                std::cout << "Caso 2: tío rojo" << std::endl;
                parent->setColor(BLACK);
                uncle->setColor(BLACK);
                grandparent->setColor(RED);
                node = grandparent;
            } else { // Caso 3: tío negro
                if (node == parent->getRight()) { // Caso 3.2: nodo es hijo derecho de su padre
                    std::cout << "Caso 3.2: zig-zag izquierdo" << std::endl;
                    node = parent;
                    left_rotation(node);
                }
                // Caso 3.1: nodo es hijo izquierdo de su padre
                std::cout << "Caso 3.1: línea recta izquierda" << std::endl;
                parent->setColor(BLACK);
                grandparent->setColor(RED);
                right_rotation(grandparent);
            }
        } else { // Caso en el que el padre está a la derecha del abuelo
            RBNode* uncle = grandparent->getLeft();
            
            if (uncle && uncle->getColor() == 'R') { // Caso 2: tío rojo
                std::cout << "Caso 2: tío rojo" << std::endl;
                parent->setColor(BLACK);
                uncle->setColor(BLACK);
                grandparent->setColor(RED);
                node = grandparent;
            } else { // Caso 3: tío negro
                if (node == parent->getLeft()) { // Caso 3.2: nodo es hijo izquierdo de su padre
                    std::cout << "Caso 3.2: zig-zag derecho" << std::endl;
                    node = parent;
                    right_rotation(node);
                }
                // Caso 3.1: nodo es hijo derecho de su padre
                std::cout << "Caso 3.1: línea recta derecha" << std::endl;
                parent->setColor(BLACK);
                grandparent->setColor(RED);
                left_rotation(grandparent);
            }
        }
    }
    root->setColor(BLACK); // Asegurar que la raíz siempre sea negra
}



RotationType RB::getRotationType(RBNode* node){
	/*this will run if node is unbalanced*/
	RotationType rType = RotationType::case_1;
	//TODO
	return rType;
}

void RB::left_rotation(RBNode* node) {
    std::cout << "****left-rotation " << node->getData() << std::endl;
    // Obtener el hijo derecho y el padre del nodo
    RBNode* rightChild = node->getRight();
    RBNode* parent = node->getParent();
    bool isLeft = node->isLeft();  // Verificar si el nodo es hijo izquierdo del padre

    // Realizar la rotación: el hijo derecho se convierte en el nuevo padre
    node->setRight(rightChild->getLeft());
    if (rightChild->getLeft() != nullptr) {
        rightChild->getLeft()->setParent(node);
    }

    rightChild->setLeft(node);
    node->setParent(rightChild);

    // Actualizar los punteros del padre
    if (node == root) {
        root = rightChild;
    } else {
        if (isLeft) {
            parent->setLeft(rightChild);
        } else {
            parent->setRight(rightChild);
        }
    }
    // Actualizar los colores de los nodos, si es necesario
    rightChild->setParent(parent);
}
void RB::right_rotation(RBNode* node) {
    std::cout << "****right-rotation " << node->getData() << std::endl;

    // Obtener el hijo izquierdo y el padre del nodo
    RBNode* leftChild = node->getLeft();
    RBNode* parent = node->getParent();
    bool isLeft = node->isLeft();  // Verificar si el nodo es hijo izquierdo del padre

    // Realizar la rotación: el hijo izquierdo se convierte en el nuevo padre
    node->setLeft(leftChild->getRight());
    if (leftChild->getRight() != nullptr) {
        leftChild->getRight()->setParent(node);
    }

    leftChild->setRight(node);
    node->setParent(leftChild);

    // Actualizar los punteros del padre
    if (node == root) {
        root = leftChild;
    } else {
        if (isLeft) {
            parent->setLeft(leftChild);
        } else {
            parent->setRight(leftChild);
        }
    }

    // Actualizar los colores de los nodos, si es necesario
    leftChild->setParent(parent);
}

void RB::rotateLeftRight(RBNode* node) {
    left_rotation(node->getLeft());
    right_rotation(node);
}

void RB::rotateRightLeft(RBNode* node) {
    right_rotation(node->getRight());
    left_rotation(node);
}

void RB::insert(int val, RBNode* node) {
    if (val < node->getData()) {
        if (node->getLeft() == nullptr) {
            node->setLeft(new RBNode(val, node));  
            balance(node->getLeft());  // Balancea después de la inserción
        } else {
            insert(val, node->getLeft());
        }
    } else {
        if (node->getRight() == nullptr) {
            node->setRight(new RBNode(val, node));  
            balance(node->getRight());  // Balancea después de la inserción
        } else {
            insert(val, node->getRight());
        }
    }
}

void RB::insert(int val){
	if (root == nullptr){
		root = new RBNode(val);
	}
	else{
		insert(val, root);
	}
	
}

RBNode* RB::find(int val, RBNode* node){
	RBNode* ans = nullptr;
	if (node->getData() == val){
		ans = node;
	}
	else{
		if (val < node->getData()){
			find(val, node->getLeft());
		}
		else{
			find(val, node->getRight());
		}
	}
	return ans;
}

RBNode* RB::find(int val){
	RBNode* ans = nullptr;
	ans = find(val, root);
	return ans;
}

void RB::traverse(RBNode* node, int label){
	if (node != nullptr){
		for (int i = 0; i < label; i++){
			std::cout << "*" << std::flush;
		}
		char T = node->isLeft()?'L':'R';
		std::cout << node->getData() << "  " << T <<std::endl;
		traverse(node->getLeft(), label + 1);
		traverse(node->getRight(), label + 1);
	}
}

void RB::traverse(){
	traverse(root, 1);
}

RB::~RB() {
	delete root;
}

} /* namespace trees */
