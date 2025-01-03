#include <iostream>
#include <sstream>
#include<string>
using namespace std;


#define MAX(X,Y) ((X>Y) ? X : Y)
#define HEIGHT(n) (n == NULL? 0 : n->getHeight())
#define ISLEAF(n) (n->getLeft() == NULL && n->getRight() == NULL? true :false)

/****************************************************************************************/
/*                                 BSTNode Prototype                                    */
/****************************************************************************************/

template <typename ITEM>
class BSTNode
{
protected:
    ITEM item;
    BSTNode <ITEM>* left;
    BSTNode <ITEM>* right;
    BSTNode <ITEM>* parent;
public:
    BSTNode();
    BSTNode(ITEM p_item);
    void setLeft(BSTNode <ITEM>* l);
    void setRight(BSTNode <ITEM>* r);
    void setParent(BSTNode <ITEM>* p);
    BSTNode<ITEM>* getLeft();
    BSTNode<ITEM>* getRight();
    BSTNode<ITEM>* getParent();
    BSTNode<ITEM>* compareAndAdvance(const ITEM& p_item);
    ITEM& getItem();
    BSTNode<ITEM>* extractAndCompareIP(const ITEM& p_item);



    ~BSTNode();
};
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                                 BSTNode Implementation                               */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


template <typename ITEM> BSTNode<ITEM>::BSTNode() { left = right = parent = NULL; }
template <typename ITEM> BSTNode<ITEM>::BSTNode(ITEM p_item) :BSTNode() { item = p_item; }
template <typename ITEM> void BSTNode<ITEM>::setLeft(BSTNode <ITEM>* l) { left = l; }
template <typename ITEM> void BSTNode<ITEM>::setRight(BSTNode <ITEM>* r) { right = r; }
template <typename ITEM> void BSTNode<ITEM>::setParent(BSTNode <ITEM>* p) { parent = p; }
template <typename ITEM> BSTNode<ITEM>* BSTNode<ITEM>::getLeft() { return left; }
template <typename ITEM> BSTNode<ITEM>* BSTNode<ITEM>::getRight() { return right; }
template <typename ITEM> BSTNode<ITEM>* BSTNode<ITEM>::getParent() { return parent; }
template <typename ITEM> BSTNode<ITEM>* BSTNode<ITEM>::compareAndAdvance(const ITEM& p_item)
{

    if (item > p_item)  return left;
    else if (item < p_item)  return right;
    else return this;
}
template <typename ITEM> ITEM& BSTNode<ITEM>::getItem() { return item; }//made getItem return the IP 
template <typename ITEM> BSTNode<ITEM>::~BSTNode()
{
    if (left != NULL) delete(left);
    if (right != NULL) delete(right);
}


template <typename ITEM> BSTNode<ITEM>* BSTNode<ITEM>::extractAndCompareIP(const ITEM& p_item) {
    string token = "";
    string item1[4];//number of groups in the ip address delimited by a '.'
    string item2[4];
    stringstream izz(item.getip());
    stringstream iss(p_item.getip());
    int i = 0, j = 0;
    while (getline(iss, token, '.')) {//putting the numbers groups into an array 
        item1[i] = token;//item being inserted 
        i++;
    }
    while (getline(izz, token, '.')) {//item were comparing to 
        item2[j] = token;
        j++;

    }

    for (int i = 0;i < item1.size();i++) {
        for (int j = 0;j < item2.size();i++) {
            if (item1[i] > item2[j]) {
                return right;
            }
            else if (item1[i] < item2[j]) {
                return left;
            }
            else {
                continue;//if we reached here then the value at both indexes is the same 
            }
        }
    }
    //if we reached the end of the arrays and both are the same so none of the return left/right executed will
    //return this(same concept as compare and advance)
    return this;


}