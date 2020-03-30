#include <iostream>
#include <vector>


using namespace std;


template<typename T>
bool comparePoints(vector<T> *p1,vector<T> *p2,int k){
    for (int i=0;i<k;i++){
        if((*p1)[i] != (*p2)[i])
            return false;
    }
    return true;
}



template<typename T>
class Node{
public:
    int A; // It's calculated as A = D mod K where the point is at depth D
    int k; //number of dimensions
    int D; // Depth of the node

    Node<T> * left, * right;
    vector<T>* point;

    Node(int k){
        this-> k = k;
        left = nullptr;
        right = nullptr;
        point = nullptr;

    }

    void setD(int d){
        this->D =d;
    };

    void insert(Node<T>* newNode){
        A = D % k; //plane of comparison 0,1,2 ... k-1
        T m = (*point)[A]; //the valua at A position

        T n = (*(newNode->point))[A];

        if (m <= n ){
            if (!right){
                newNode->setD(D+1);
                right = newNode;
            } else
                right->insert(newNode);
        }

        if (n < m ){
            if(!left){
                newNode->setD(D+1);
                left = newNode;
            } else
                left->insert(newNode);
        }

    }

    bool search(vector<T> *_point){

        if (comparePoints(point, _point, k)){
            return true;
        }

        A = D % k; //plane of comparison 0,1,2 ... k-1


        T m = (*point)[A]; //the valua at A position
        T n = (*_point)[A]; // the value at A position

        if (m <= n){
            if(!right)
                return false;
            return right->search(_point);
        }
        if (n < m){
            if(!left)
                return false;
            return left->search(_point);

        }


    }


    void setPoint(vector<T>* _point){
        point = new vector<T>;

        for (T i: * _point)
            point->push_back(i);
    };

    void print(){
        cout << "( ";
        for (T i: *point)
            cout << i << " ";

        cout << ") ";
    }


};

template <typename T>
bool printLevel(Node<T> *root,int level ){
    if (!root)
        return false;


    if (level == 1)
    {
        root->print();
        return true;
    }

    bool left = printLevel(root->left, level -1);
    bool right = printLevel(root->right, level - 1);


    return left || right;

}



template <typename T, int K>
class KDTree{
public:
    Node<T>* root;
    int k; //number of dimensions


    KDTree(){
        root = nullptr;
        this->k = K;
    }
    void insert(vector<T> *point){
        if (!root){
            root = new Node<T>(k);
            root->setPoint(point);
            root->setD(0);

        } else{
            Node<T> *temp = new Node<T>(k);
            temp->setPoint(point);
            root->insert(temp);
        }
    }

    bool search(vector<T> *point){
        if(!root)
            return false;
        return root->search(point);

    }


    void printLevelOrder(){
        int level = 1;
        cout << "Imprimiendo arbol :"<< endl;

        while (printLevel(root, level)){
            cout << " => level "<< level << endl;
            level ++;
        }

    }
};





int main() {

    // Create a K-D tree
    auto *k =  new KDTree<int, 2>;

    // Inserting Points
    auto p1 = new vector<int>{3,6};
    auto p2 = new vector<int>{17,15};
    auto p3 = new vector<int>{13,15};
    auto p4 = new vector<int>{6,12};
    auto p5 = new vector<int>{9,1};
    auto p6 = new vector<int>{2,7};
    auto p7 = new vector<int>{10,19};
    k->insert(p1);
    k->insert(p2);
    k->insert(p3);
    k->insert(p4);
    k->insert(p5);
    k->insert(p6);
    k->insert(p7);

    //Creating a point that is not in the tree
    auto q1 = new vector<int>{3,7};

    //Searching points
    k->search(p2)? cout << "Found\n": cout << "Not Found\n";
    k->search(p3)? cout << "Found\n": cout << "Not Found\n";
    k->search(q1)? cout << "Found\n": cout << "Not Found\n";

    //Printing the tree
    k->printLevelOrder();

    return 0;
}

