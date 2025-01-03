
#include "BSTNode.hpp"
/****************************************************************************************/
/*                            BinarySearchTree Prototype                                */
/****************************************************************************************/



template <class NODE, typename ITEM>
class BinarySearchTree
{
protected:
    NODE* root;
    int count;
    void traverseASC(NODE* n);
    void traverseDESC(NODE* n);
    NODE* insert(NODE* n, const ITEM& p_item);

public:
    BinarySearchTree();
    virtual NODE* insert1(const ITEM& item);
    virtual bool remove1(const ITEM& item);
    void traverseDESC();
    void traverseASC();
    NODE* findMax(NODE* n = NULL);
    NODE* findMin(NODE* n = NULL);
    bool contains(const ITEM item);
    NODE* find(const ITEM item);
    int getCount();
    NODE* getRoot();
    NODE* rangeSearch(string lowdate, string lowtime,string highdate,string hightime, string& key, NODE* n);
    virtual ~BinarySearchTree();
};

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                        BinarySearchTree Implementation                               */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


template <class NODE, typename ITEM> void BinarySearchTree<NODE, ITEM>::traverseASC(NODE* n)
{
    if (n == NULL) return;
    traverseASC(n->getLeft());
    cout << n->getItem() << endl;
    traverseASC(n->getRight());
}
template <class NODE, typename ITEM> void BinarySearchTree<NODE, ITEM>::traverseDESC(NODE* n)
{
    if (n == NULL) return;
    traverseDESC((NODE*)n->getRight());
    cout << n->getItem() << endl;
    traverseDESC((NODE*)n->getLeft());
}

template <class NODE, typename ITEM> NODE* BinarySearchTree<NODE, ITEM>::insert(NODE* n, const ITEM& p_item)
{
    if (n->getItem() > p_item) {
        if (n->getLeft() == NULL) {
            NODE* new_node = new NODE(p_item);
            n->setLeft(new_node);
            new_node->setParent(n);
            return new_node;
        } return NULL;
    }
    else if (n->getItem() < p_item)
    {
        if (n->getRight() == NULL) {
            NODE* new_node = new NODE(p_item);
            n->setRight(new_node);
            new_node->setParent(n);
            return new_node;
        }
        else return NULL;
    }
    else return NULL;
}

template <class NODE, typename ITEM> BinarySearchTree<NODE, ITEM>::BinarySearchTree()
{
    root = NULL;
    count = 0;
}

template <class NODE, typename ITEM> NODE* BinarySearchTree<NODE, ITEM>::insert1(const ITEM& item)
{
    NODE* new_node = NULL;
    if (root == NULL)
    {
        new_node = root = new NODE(item);
    }
    else
    {
        NODE* parent = root;
        NODE* next = (NODE*)parent->compareAndAdvance(item);
        while (next != parent)
        {
            if (next == NULL) { new_node = (NODE*)insert(parent, item); break; }
            else parent = next;
            next = (NODE*)parent->compareAndAdvance(item);
        }
    }
    if (new_node != NULL) count++;
    return new_node;
}

template <class NODE, typename ITEM> bool BinarySearchTree<NODE, ITEM>::remove1(const ITEM& item)
{
    NODE* search_node = find(item);
    if (search_node != NULL)
    {
        //search_node->setCascadeDelete(false);
        NODE* parent = (NODE*)search_node->getParent();
        bool left_child = false;
        if (parent != NULL && parent->getLeft() == search_node) left_child = true;
        if (parent == NULL) { // If root
            if (search_node->getRight() == NULL) root = search_node->getLeft();
            else if (search_node->getLeft() == NULL) root = search_node->getRight();
            else {
                NODE* min = findMin((NODE*)search_node->getRight());
                if (min == NULL) exit(1);
                if (min->getParent() != NULL) {
                    if (min->getParent()->getLeft() == min)
                        min->getParent()->setLeft(min->getRight());
                    else if (min->getParent()->getRight() == min)
                        min->getParent()->setRight(min->getRight());
                    if (min->getRight() != NULL) min->getRight()->setParent(min->getParent());
                }
                min->setParent(parent);
                min->setLeft(search_node->getLeft());
                min->setRight(search_node->getRight());
                if (min->getLeft() != NULL) min->getLeft()->setParent(min);
                if (min->getRight() != NULL)  min->getRight()->setParent(min);
                root = min;
            }
            if (root != NULL) root->setParent(NULL);
        }
        else if (search_node->getLeft() != NULL && search_node->getRight() != NULL)  // Two Children
        {
            NODE* min = findMin((NODE*)search_node->getRight());
            if (search_node->getRight() == min)
            {
                min->setParent(search_node->getParent());
                if (left_child) search_node->getParent()->setLeft(min);
                else search_node->getParent()->setRight(min);
                min->setLeft(search_node->getLeft());
                if (min->getLeft() != NULL) min->getLeft()->setParent(min);
                if (min->getRight() != NULL)  min->getRight()->setParent(min);
            }
            else
            {
                if (min->getParent() != NULL) min->getParent()->setLeft(min->getRight());
                if (min->getRight() != NULL) min->getRight()->setParent(min->getParent());
                if (left_child) parent->setLeft(min);
                else parent->setRight(min);
                min->setParent(parent);
                min->setRight(search_node->getRight());
                min->setLeft(search_node->getLeft());
                if (min->getLeft() != NULL) min->getLeft()->setParent(min);
                if (min->getRight() != NULL)  min->getRight()->setParent(min);
            }
        }
        else if (search_node->getLeft() != NULL) {          // One Left Children
            if (left_child) parent->setLeft(search_node->getLeft());
            else parent->setRight(search_node->getLeft());
            search_node->getLeft()->setParent(parent);
        }
        else if (search_node->getRight() != NULL) {             // One Right Children
            if (left_child) parent->setLeft(search_node->getRight());
            else parent->setRight(search_node->getRight());
            search_node->getRight()->setParent(parent);
        }
        else {                   // Leaf Node
            if (left_child) parent->setLeft(NULL);
            else parent->setRight(NULL);
        }
        count--;
        search_node->setLeft(NULL);
        search_node->setRight(NULL);
        delete (search_node);
        return true;
    }
    return false;



}

template <class NODE, typename ITEM> NODE* BinarySearchTree<NODE, ITEM>::findMax(NODE* n)
{
    if (root == NULL) return NULL;
    if (n == NULL) return findMax(root);
    else if (n->getRight() == NULL) return n;
    else return findMax((NODE*)n->getRight());
}
template <class NODE, typename ITEM> NODE* BinarySearchTree<NODE, ITEM>::findMin(NODE* n)
{
    if (root == NULL) return NULL;
    if (n == NULL) return findMin(root);
    else if (n->getLeft() == NULL) return n;
    else return findMin((NODE*)n->getLeft());
}

template <class NODE, typename ITEM> void BinarySearchTree<NODE, ITEM>::traverseASC()
{
    traverseASC(root);
}
template <class NODE, typename ITEM> void BinarySearchTree<NODE, ITEM>::traverseDESC()
{
    traverseDESC(root);
}
template <class NODE, typename ITEM> bool BinarySearchTree<NODE, ITEM>::contains(const ITEM item)
{
    if (find(item) == NULL) return false;
    else return true;
}

template <class NODE, typename ITEM> NODE* BinarySearchTree<NODE, ITEM>::find(const ITEM item)
{
    if (root != NULL)
    {
        NODE* parent = root;
        NODE* next = (NODE*)parent->compareAndAdvance(item);
        while (next != parent)
        {
            if (next == NULL) break;
            else parent = next;
            next = (NODE*)parent->compareAndAdvance(item);
        }
        if (next == parent) return next;
    }
    return NULL;
}

template <class NODE, typename ITEM> int BinarySearchTree<NODE, ITEM>::getCount()
{
    return count;
}

template <class NODE, typename ITEM> NODE* BinarySearchTree<NODE, ITEM>::getRoot()
{
    return root;
}


//RANGE SEARCH FUNCTION IMPLEMENTATION 
template <class NODE, typename ITEM> NODE* BinarySearchTree<NODE, ITEM>::rangeSearch(string lowdate, string lowtime,string highdate,string hightime, string& key, NODE* n)
{

    if (n == NULL) {//empty tree
        return NULL;
    }
    else if (n->getItem().getip() == key) {//ip is found
        return n;
    }
    else if ((n->getItem().getdate()>=highdate) and ((n->getItem().getdate() == highdate) or (n->getItem().gettime()>=hightime))) {
        return rangeSearch(lowdate,lowtime,highdate, hightime, key, n->getLeft());//search on left side bcs date and time are less than those of the node were at(within range)
    }
    else if ((n->getItem().getdate()<=lowdate) or ((n->getItem().getdate() == lowdate) and (n->getItem().gettime()<=lowtime))) {
        return rangeSearch(lowdate, lowtime, highdate, hightime, key, n->getRight());//search on right bcs date and time are bigger than those of the node were at(within range)
    }
    else if((n->getItem().getdate() >= lowdate and n->getItem().gettime() >= lowtime) and (n->getItem().getdate() <= highdate and n->getItem().gettime() <= hightime)) {//handling the case that the date and time of the node are within range but the key doesnt match
        return NULL;
    } 
    else {
        return rangeSearch(lowdate, lowtime, highdate, hightime, key, n);//key is within those bounds so will call function 
        //again and keep checking on each root we get with conditions above by recursion
    }
}

template <class NODE, typename ITEM> BinarySearchTree<NODE, ITEM>::~BinarySearchTree()
{
    if (root != NULL) delete (root);
}

//int main() {
//    BinarySearchTree<BSTNode<int>, int> t;
//    t.insert1(5);
//    t.insert1(3);
//    t.insert1(7);
//    t.insert1(6);
//    t.insert1(8);
//    t.insert1(2);
//    t.insert1(4);
//    t.insert1(9);
//    cout<<"Item found at node with adress: "<<t.rangeSearch(3, 7, 5, t.getRoot());
//}