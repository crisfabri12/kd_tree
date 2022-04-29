#include <cmath>
#include <iostream>
#include <set>
#include <stdexcept>
#include <utility>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include "Point.hpp"
#include <limits.h>
using namespace std;

 template <size_t N>
struct KDNode
{
    Point<N> point;
    int depth;
    int value;
    KDNode<N>* children[2];
    KDNode(Point<N> _point, int _value, int _depth) {
        point = _point;
        depth = _depth;
        value = _value;
        children[0] = children[1] = 0;
    }
};

 template <size_t N> 
class KDTree {
 public:
  typedef pair<Point<N>, int> value_type;

  KDTree();

  size_t dimension() const;   
  size_t size() const;         

  void insert(const Point<N> &pt, const int &value);   //inserta un punto
  int knn(const Point<N> &key, size_t k) const; //knn mas cercano, retorna el valor mas comun de los k mas cercanos
  vector<int> knn_query(const Point<N> &key, size_t k) const;  //devuelve vector con los vecinos mas cercanos    
  void find_neighbors(const Point<N>& key, KDNode<N>* currentNode, vector<tuple<double, KDNode<N>*>> &NNqueue, int k, int depth) const;

 private:
  size_t dimension_;        
  size_t size_;             
  KDNode<N>* root;
};

 template <size_t N>
KDTree<N>::KDTree() {
    dimension_ = N;
    size_ = 0;
    root = nullptr;
}

 template <size_t N>
size_t KDTree<N>::dimension() const {
    return dimension_;
}

 template <size_t N>
size_t KDTree<N>::size() const {
    return size_;
}


 template <size_t N>
void KDTree<N>::insert(const Point<N> &pt, const int &value) {
    KDNode<N>** p = nullptr;
    int _depth = 0;
    for (p = &root;
        *p && (*p)->point != pt;
        p = &((*p)->children[pt[_depth % N] > (*p)->point[_depth % N]]), _depth++);
    if (*p == 0) {
        *p = new KDNode<N>(pt,value, _depth);
        size_++;
    }
    else
        (*p)->value = value;
}


 template <size_t N>
void KDTree<N>::find_neighbors(const Point<N>& key, KDNode<N>* currentNode, vector<tuple<double, KDNode<N>*>>& NNqueue, int k, int depth) const {
    if (!currentNode)
        return;
    NNqueue.push_back(make_tuple(distances<N>(key, currentNode->point), currentNode));
    sort(NNqueue.begin(), NNqueue.end());
    if (NNqueue.size() > k)
        NNqueue.pop_back();
    int axis = depth % dimension_;
    bool right = false;
    if (key[axis] < currentNode->point[axis]) {
        right = true;
        find_neighbors(key, currentNode->children[0], NNqueue, k, ++depth);
    }
    else {
        right = false;
        find_neighbors(key, currentNode->children[1], NNqueue, k, ++depth);
    }
    if (fabs(currentNode->point[axis] - key[axis]) < get<0>(*(NNqueue.end() - 1))) {
        if(right)
            find_neighbors(key, currentNode->children[0], NNqueue, k, ++depth);
        else
            find_neighbors(key, currentNode->children[1], NNqueue, k, ++depth);
    }
}

 template <size_t N>
int KDTree<N>::knn(const Point<N> &key, size_t k) const {
    vector<int> values = knn_query(key, k);
    
    vector<tuple<int, int>> counts;
    for (vector<int>::iterator it = values.begin(); it != values.end(); it++) {
        counts.push_back(make_tuple(count(values.begin(),values.end(),*it),*it));
    }
    sort(counts.begin(), counts.end());
    reverse(counts.begin(), counts.end());

    int new_element = get<1>(counts[0]);
    return new_element;
}

 template <size_t N>
vector<int> KDTree<N>::knn_query(const Point<N> &key, size_t k) const {
    vector<tuple<double, KDNode<N>*>> NNqueue;
    find_neighbors(key, root, NNqueue, k, 0);
    
    vector<int> values;
    for (typename vector<tuple<double, KDNode<N>*>>::iterator it = NNqueue.begin(); it != NNqueue.end(); it++){
        values.push_back(get<1>(*it)->value);
    }
    return values;
}
