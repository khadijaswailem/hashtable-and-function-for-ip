//

//
//NOW WERE WORKING ON TEST 2 TO DEVELOP THE RIGHT AND LEFT ROTATIONS CODE MORE PRECISLEY AND 
//HENCE EDITING THE DOUBLE ROTATIONS CODE TOO

#include "AVLNode.hpp"
/****************************************************************************************/
/*                                 AVLTree Prototype                                    */
/****************************************************************************************/


template <typename ITEM>
class AVLTree : public BinarySearchTree<AVLNode<ITEM>, ITEM>
{
private:
    AVLNode <ITEM>* updateHeightAndEvaluateBalance(AVLNode <ITEM>* n);
    void rotateWithLeftChild(AVLNode <ITEM>* p);
    void rotateWithRightChild(AVLNode <ITEM>* p);
    void doubleRotateWithLeftChild(AVLNode <ITEM>* p);
    void doubleRotateWithRightChild(AVLNode <ITEM>* p);
    int calcHeight(AVLNode <ITEM>* n);
    bool isBalanced(AVLNode <ITEM>* n);
public:
    AVLTree();
    AVLNode <ITEM>* insert(const ITEM& item);
    int calcHeight();  // This is needed for the isBalanaced
    bool remove(const ITEM& item);
    void traverse(AVLNode <ITEM>* n = NULL, int depth = 0);
    bool isBalanced();
    ~AVLTree();
};

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                               AVLTree Implementation                                 */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

//CALCULATING HEIGHT
template <typename ITEM> int AVLTree<ITEM>::calcHeight(AVLNode <ITEM>* n)
{
    if (n == NULL) {

        return -1;

    }
    int lheight = calcHeight(n->getLeft());//gettng height of left subtree till last node
    int rheight = calcHeight(n->getRight());//getting height of right subtree till last node
    if (lheight > rheight) {//checking which subtree has higher height
        return (lheight + 1);
    }
    else {
        return (rheight + 1);//returning that height +1 since if theres no left/right 
        //meaning its a leaf then in this case only base case will execute and since that returns -1 and leaves are 
        // always at height zero we will add 1 to the -1 and since the base case will execute 
        //at the end of either subtracting from height we also add 1 to make the height correct
    }
    return 0;
}

//UPDATE & EVALUATE METHOD 
template <typename ITEM>  AVLNode <ITEM>* AVLTree<ITEM>::updateHeightAndEvaluateBalance(AVLNode <ITEM>* n)
{


    if (n == NULL) {//if node were cehcking is null

        return NULL;
    }

    int leftHeight;
    int rightHeight;


    if (n->getLeft() != NULL) {//storing the height of left subtree if it exists 
        leftHeight = n->getLeft()->getHeight();
    }
    else {
        leftHeight = -1;//-1 if it doesnt exist meaning might be a leaf
    }
    if (n->getRight() != NULL) {//storing height of right subtree if it exists
        rightHeight = n->getRight()->getHeight();
    }
    else {
        rightHeight = -1; //if it doesnt meaning might be a leaf
    }
    if (leftHeight > rightHeight) { //pick out of the two heights of the left and right subtree which is bigger and setting the height of current node to that
        n->setHeight(leftHeight + 1);
    }
    else {
        n->setHeight(rightHeight + 1);
    }

    if (!isBalanced(n)) {
        return n;
    }
    else {
        return NULL;
    }
}


//ACTS AS A RIGHT ROTATION 
template <typename ITEM> void AVLTree<ITEM>::rotateWithLeftChild(AVLNode <ITEM>* p)
{


    AVLNode<ITEM>* x = p->getLeft();
    if (x == NULL)return;//to make sure that the pointer were trying to get its right isnt null 
    p->setLeft(x->getRight());

    x->setParent(p->getParent());
    if (x->getRight() != NULL) {
        x->getRight()->setParent(p);
    }


    if (p->getParent() == NULL) {
        this->root = x;
    }
    else if (p == p->getParent()->getLeft()) {
        p->getParent()->setLeft(x);
    }
    else {
        p->getParent()->setRight(x);
    }
    x->setRight(p);
    p->setParent(x);

    p->setHeight(MAX(HEIGHT(p->getLeft()), HEIGHT(p->getRight())));//updating the height of both the x and the p after the insertion
    x->setHeight(MAX(HEIGHT(x->getLeft()), HEIGHT(x->getRight())));

}

//ACTS AS A LEFT ROTATION 
template <typename ITEM> void AVLTree<ITEM>::rotateWithRightChild(AVLNode <ITEM>* p)
{

    AVLNode<ITEM>* x = p->getRight();
    if (x == NULL)return;
    p->setRight(x->getLeft());

    x->setParent(p->getParent());
    if (x->getLeft() != NULL) {
        x->getLeft()->setParent(p);
    }


    if (p->getParent() == NULL) {
        this->root = x;
    }
    else if (p == p->getParent()->getLeft()) {
        p->getParent()->setLeft(x);
    }
    else {
        p->getParent()->setRight(x);
    }

    x->setLeft(p);
    p->setParent(x);

    p->setHeight(MAX(HEIGHT(p->getLeft()), HEIGHT(p->getRight())));
    x->setHeight(MAX(HEIGHT(x->getLeft()), HEIGHT(x->getRight())));
}

// ACTS AS A RIGHT ROTATION FOLLOWED BY A LEFT ROTATION 
template <typename ITEM> void AVLTree<ITEM>::doubleRotateWithLeftChild(AVLNode <ITEM>* p)
{
    rotateWithLeftChild(p->getRight());
    rotateWithRightChild(p);

}

//ACTS AS A LEFT ROTATION FOLLOWED BY A RIGHT ROTATION 
template <typename ITEM> void AVLTree<ITEM>::doubleRotateWithRightChild(AVLNode <ITEM>* p)
{
    rotateWithRightChild(p->getLeft());
    rotateWithLeftChild(p);
}



//CHECKING BALANCE 
template <typename ITEM> bool AVLTree<ITEM>::isBalanced(AVLNode <ITEM>* n)
{
    if (n == NULL) {//case tree is empty

        return true;
    }
    int lheight = calcHeight(n->getLeft());//getting height of left subtree
    int rheight = calcHeight(n->getRight());//getting height of right subtree
    int bf = lheight - rheight;//getting balance factor for root
    if (bf > 1 or bf < -1) {

        return false;//if root is unbalanced then tree is automatically unbalanced 
    }

    bool ltreecheck = isBalanced(n->getLeft());
    bool rtreecheck = isBalanced(n->getRight());

    if (ltreecheck == false or rtreecheck == false) {

        return false;
    }

    return true;
}

//CONSTRUCTOR 
template <typename ITEM> AVLTree<ITEM>::AVLTree() :BinarySearchTree<AVLNode<ITEM>, ITEM>() {}

//INSERT METHOD
template <typename ITEM> AVLNode <ITEM>* AVLTree<ITEM>::insert(const ITEM& item) {

    if (this->contains(item)) {
        cout << "This element already exists in the tree" << endl;
        return NULL;
    }
    cout << "Inserting: " << item << endl;
    AVLNode<ITEM>* node = this->insert1(item);//calling the inherited insert 
    AVLNode<ITEM>* temp = node;//creating another pointer to the node we just inserted 


    while (temp != NULL) {//we loop from bottom of the tree upwards and fix any imbalances 
        //temp each time will get assigned to the parent node of the one were standing at 
        if (updateHeightAndEvaluateBalance(temp) != NULL) {//if after insertion tree not balanced then updateheightevalbalance wouldnt return null hence will know it needs balancing 
            int bf = calcHeight(temp->getLeft()) - calcHeight(temp->getRight());//calculating bf of node 
            if (bf > 1 and (calcHeight(temp->getLeft()->getLeft()) > calcHeight(temp->getLeft()->getRight()))) {//meaning that both nodes are on the left,node left left height =0 and node left right height =-1

                rotateWithLeftChild(temp);//passing the node with imbalance to the functions to fix it 

            }
            else if (bf < -1 and (calcHeight(temp->getRight()->getRight()) > calcHeight(temp->getRight()->getLeft()))) {//both nodes are on the right so node right right height =0 and node right left =-1
                rotateWithRightChild(temp);
            }
            else if (bf > 1 and (calcHeight(temp->getLeft()->getLeft()) < calcHeight(temp->getLeft()->getRight()))) {//node left left height =-1 node left right height =0
                doubleRotateWithRightChild(temp);
            }
            else {
                doubleRotateWithLeftChild(temp);

            }


        }
        temp = temp->getParent();//to keep moving upwards in the tree to avoid an infinite while,acts as the iterator in this loop
    }
    return temp;


}


//HEIGHT OF TREE
template <typename ITEM> int AVLTree<ITEM>::calcHeight()
{

    return calcHeight(this->root);
}

//IF TREE IS BALANCED 
template <typename ITEM> bool AVLTree<ITEM>::isBalanced()
{
    if (isBalanced(this->root)) {
        cout << "Tree is Balanced" << endl;
    }
    else {
        cout << "Tree is Imbalanced" << endl;
    }
    return isBalanced(this->root);
}


//REMOVE METHOD 
template <typename ITEM> bool AVLTree<ITEM>::remove(const ITEM& item) {
    if (this->contains(item) == true) {//checking if item we want to remove is in the tree
        AVLNode<ITEM>* temp = this->find(item).getParent();//creating another pointer to the node we just removed 

        this->remove1(item);//called this method from parent class we inherited from

        while (temp != NULL) {//we loop from bottom of the tree upwards and fix any imbalances 
            //temp each time will get assigned to the parent node of the one were standing at 
            if (updateHeightAndEvaluateBalance(temp) != NULL) {//if after insertion tree not balanced then updateheightevalbalance wouldnt return null hence will know it needs balancing 
                int bf = calcHeight(temp->getLeft()) - calcHeight(temp->getRight());//calculating bf of node 
                if (bf > 1 and (calcHeight(temp->getLeft()->getLeft()) > calcHeight(temp->getLeft()->getRight()))) {//meaning that both nodes are on the left,node left left height =0 and node left right height =-1

                    rotateWithLeftChild(temp);//passing the node with imbalance to the functions to fix it 

                }
                else if (bf < -1 and (calcHeight(temp->getRight()->getRight()) > calcHeight(temp->getRight()->getLeft()))) {//both nodes are on the right so node right right height =0 and node right left =-1
                    rotateWithRightChild(temp);
                }
                else if (bf > 1 and (calcHeight(temp->getLeft()->getLeft()) < calcHeight(temp->getLeft()->getRight()))) {//node left left height =-1 node left right height =0
                    doubleRotateWithRightChild(temp);
                }
                else {
                    doubleRotateWithLeftChild(temp);

                }


            }
            temp = temp->getParent();//to keep moving upwards in the tree to avoid an infinite while,acts as the iterator in this loop
        }
        cout << "Element removed sucessfully" << endl;
        return true;

    }
    else {
        cout << "This element doesnt exist in this tree" << endl;
        return false;
    }

}



//TRAVERSE METHOD MADE IT ASC BY DEFAULT 
template <typename ITEM> void AVLTree<ITEM>::traverse(AVLNode <ITEM>* n, int depth) {
    if (n == NULL) {
        return;
    }
    traverse(n->getLeft(), depth + 1);
    cout << n->getItem() << endl;
    traverse(n->getRight(), depth + 1);


}


//DESTRUCTOR
template <typename ITEM> AVLTree<ITEM>::~AVLTree() {}



