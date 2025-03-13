//
// Created by 30884 on 25-3-11.
//

#ifndef AVL_TREE_AVLTREE_H
#define AVL_TREE_AVLTREE_H

#include <vector>
#include <iostream>
#include <stack>
#include <queue>

// 定义 key_value_pair 类
template <class KeyType, class ValueType>
class key_value_pair {
public:
    KeyType key;
    ValueType value;

    key_value_pair() = default;

    key_value_pair(const KeyType &k,const ValueType &v) {
        this->key = k;
        this->value = v;
    }

    virtual ~key_value_pair() = default;

    void setData(const KeyType &k,const ValueType &v) {
        this->key = k;
        this->value = v;
    }
};

// 定义 TreeNode 类
template <class KeyType, class ValueType>
class TreeNode {
public:
    key_value_pair<KeyType, ValueType> pair;
    TreeNode *leftChild;
    TreeNode *rightChild;
    int height;

    TreeNode() {
        this->leftChild = nullptr;
        this->rightChild = nullptr;
        height = 1;
    }

    TreeNode(const KeyType &k,const ValueType &v) {
        this->pair.setData(k, v);
        this->leftChild = nullptr;
        this->rightChild = nullptr;
        height = 1;
    }

    TreeNode(const KeyType &k,const ValueType &v, TreeNode *l, TreeNode *r, int h = 1) {
        this->pair.setData(k, v);
        this->leftChild = l;
        this->rightChild = r;
        this->height = h;
        height = 1;
    }

    virtual ~TreeNode() = default;
};

// 定义 AVL_tree 类
template <class KeyType, class ValueType>
class AVL_tree {
private:
    TreeNode<KeyType, ValueType> *root;

    void insert(const key_value_pair<KeyType, ValueType> &pair, TreeNode<KeyType, ValueType> *&t);
    bool remove(const KeyType &x, TreeNode<KeyType, ValueType> *&t);
    void makeEmpty(TreeNode<KeyType, ValueType> *t);
    int max(int a, int b) { return (a > b) ? a : b; }
    int height(TreeNode<KeyType, ValueType> *t) const { return t == nullptr ? 0 : t->height; }
    void LL(TreeNode<KeyType, ValueType> *&t);
    void LR(TreeNode<KeyType, ValueType> *&t);
    void RL(TreeNode<KeyType, ValueType> *&t);
    void RR(TreeNode<KeyType, ValueType> *&t);
    bool adjust(TreeNode<KeyType, ValueType> *&t, int subTree);

public:
    AVL_tree();
    AVL_tree(const std::vector<key_value_pair<KeyType, ValueType>> &data);
    ~AVL_tree();

    TreeNode<KeyType, ValueType> *getRoot() const;
    TreeNode<KeyType, ValueType> *searchKey(const KeyType &k) const;
    void insertKey(const key_value_pair<KeyType, ValueType> &new_pair);
    bool removeKey(const KeyType &k);

    void clear(TreeNode<KeyType, ValueType> *target);
    void traverse(TreeNode<KeyType, ValueType> *target) const;
    void traverse() const;
    void dataStructure() const;
};

//层序遍历
template<class KeyType, class ValueType>
void AVL_tree<KeyType, ValueType>::dataStructure() const {
    if (this->root == nullptr) {
        std::cout << "The tree is empty." << std::endl;
        return;
    }

    std::queue<TreeNode<KeyType, ValueType>*> queue;
    queue.push(this->root);

    while (!queue.empty()) {
        int levelSize = queue.size(); // 当前层的节点数量
        for (int i = 0; i < levelSize; ++i) {
            TreeNode<KeyType, ValueType>* current = queue.front();
            queue.pop();

            std::cout << current->pair.key << "-" << current->pair.value << " ";

            if (current->leftChild) {
                queue.push(current->leftChild);
            }
            if (current->rightChild) {
                queue.push(current->rightChild);
            }
        }
        std::cout << std::endl; // 每层结束后换行
    }
}

// 构造函数
template <class KeyType, class ValueType>
AVL_tree<KeyType, ValueType>::AVL_tree() {
    this->root = nullptr;
}

// 带参数的构造函数
template <class KeyType, class ValueType>
AVL_tree<KeyType, ValueType>::AVL_tree(const std::vector<key_value_pair<KeyType, ValueType>> &data) {
    this->root = nullptr;
    if (data.empty()) {
        return;
    }
    for (auto item : data) {
        insertKey(item);
    }
}

// 析构函数
template <class KeyType, class ValueType>
AVL_tree<KeyType, ValueType>::~AVL_tree() {
    clear(root);
    delete this->root;
}

// 获取根节点
template <class KeyType, class ValueType>
TreeNode<KeyType, ValueType> *AVL_tree<KeyType, ValueType>::getRoot() const {
    return this->root;
}

// 中序遍历
template <class KeyType, class ValueType>
void AVL_tree<KeyType, ValueType>::traverse(TreeNode<KeyType, ValueType> *target) const {
    if (!target) {
        return;
    }
    if (target->leftChild) {
        traverse(target->leftChild);
    }
    std::cout << "Key:" << target->pair.key << " Value:" << target->pair.value << std::endl;
    if (target->rightChild) {
        traverse(target->rightChild);
    }
}

// 中序遍历（公共接口）
template <class KeyType, class ValueType>
void AVL_tree<KeyType, ValueType>::traverse() const {
    traverse(this->root);
}

// 清空树
template <class KeyType, class ValueType>
void AVL_tree<KeyType, ValueType>::clear(TreeNode<KeyType, ValueType> *target) {
    if (target->leftChild) {
        clear(target->leftChild);
    }
    if (target->rightChild) {
        clear(target->rightChild);
    }
    makeEmpty(target);
}

// 清空子树
template <class KeyType, class ValueType>
void AVL_tree<KeyType, ValueType>::makeEmpty(TreeNode<KeyType, ValueType> *t) {
    t = nullptr;
}

// 搜索键值
template <class KeyType, class ValueType>
TreeNode<KeyType, ValueType> *AVL_tree<KeyType, ValueType>::searchKey(const KeyType &k) const {
    if (!this->root) {
        return nullptr;
    }
    TreeNode<KeyType, ValueType> *searchNode = this->root;
    while (true) {
        if (searchNode->pair.key == k) {
            return searchNode;
        } else if (searchNode->pair.key < k) {
            if (!searchNode->rightChild) {
                return nullptr;
            }
            searchNode = searchNode->rightChild;
            continue;
        } else if (searchNode->pair.key > k) {
            if (!searchNode->leftChild) {
                return nullptr;
            }
            searchNode = searchNode->leftChild;
            continue;
        }
    }
}

// 插入键值对
template <class KeyType, class ValueType>
void AVL_tree<KeyType, ValueType>::insertKey(const key_value_pair<KeyType, ValueType> &new_pair) {
    insert(new_pair, this->root);
}

// 删除键值
template <class KeyType, class ValueType>
bool AVL_tree<KeyType, ValueType>::removeKey(const KeyType &k) {
    return remove(k, this->root);
}

// 插入操作（私有方法）
template <class KeyType, class ValueType>
void AVL_tree<KeyType, ValueType>::insert(const key_value_pair<KeyType, ValueType> &pair, TreeNode<KeyType, ValueType> *&t) {
    if (t == nullptr) {
        t = new TreeNode<KeyType, ValueType>(pair.key, pair.value);
    }
    else if (pair.key < t->pair.key) {
        insert(pair, t->leftChild);
        if (height(t->leftChild) - height(t->rightChild) == 2) {
            if (pair.key < t->leftChild->pair.key) {
                LL(t);
            } else {
                LR(t);
            }
        }
    }
    else if (t->pair.key < pair.key) {
        insert(pair, t->rightChild);
        if (height(t->rightChild) - height(t->leftChild) == 2) {
            if (t->rightChild->pair.key < pair.key) {
                RR(t);
            } else {
                RL(t);
            }
        }
    }
    t->height = max(height(t->leftChild), height(t->rightChild)) + 1;
}

// 删除操作（私有方法）
template <class KeyType, class ValueType>
bool AVL_tree<KeyType, ValueType>::remove(const KeyType &x, TreeNode<KeyType, ValueType> *&t) {
    if (!t) {
        return false;
    }
    if (x == t->pair.key) {
        if (!t->leftChild || !t->rightChild) {
            TreeNode<KeyType, ValueType> *oldNode = t;
            t = (t->leftChild != nullptr) ? t->leftChild : t->rightChild;
            delete oldNode;
            return true;
        } else {
            TreeNode<KeyType, ValueType> *tmp = t->rightChild;
            while (tmp->leftChild != nullptr) {
                tmp = tmp->leftChild;
            }
            t->pair = tmp->pair;
            return remove(tmp->pair.key, t->rightChild);
        }
    } else if (x < t->pair.key) {
        return remove(x, t->leftChild);
    } else {
        return remove(x, t->rightChild);
    }
}

// 平衡调整（私有方法）
template <class KeyType, class ValueType>
bool AVL_tree<KeyType, ValueType>::adjust(TreeNode<KeyType, ValueType> *&t, int subTree) {
    if (subTree) {
        if (height(t->left) - height(t->right) == 1) {
            return true;
        }
        if (height(t->right) == height(t->left)) {
            --t->height;
            return false;
        }
        if (height(t->left->right) > height(t->left->left)) {
            LR(t);
            return false;
        }
        LL(t);
        return height(t->right) == height(t->left);
    } else {
        if (height(t->right) - height(t->left) == 1) {
            return true;
        }
        if (height(t->right) == height(t->left)) {
            --t->height;
            return false;
        }
        if (height(t->right->left) > height(t->right->right)) {
            RL(t);
            return false;
        }
        RR(t);
        return height(t->right) == height(t->left);
    }
}

// 左左旋转
template <class KeyType, class ValueType>
void AVL_tree<KeyType, ValueType>::LL(TreeNode<KeyType, ValueType> *&t) {
    TreeNode<KeyType, ValueType> *t1 = t->leftChild;
    t->leftChild = t1->rightChild;
    t1->rightChild = t;
    t->height = max(height(t->leftChild), height(t->rightChild)) + 1;
    t1->height = max(height(t1->leftChild), height(t)) + 1;
    t = t1;
}

// 左右旋转
template <class KeyType, class ValueType>
void AVL_tree<KeyType, ValueType>::LR(TreeNode<KeyType, ValueType> *&t) {
    RR(t->leftChild);
    LL(t);
}

// 右右旋转
template <class KeyType, class ValueType>
void AVL_tree<KeyType, ValueType>::RR(TreeNode<KeyType, ValueType> *&t) {
    TreeNode<KeyType, ValueType> *t1 = t->rightChild;
    t->rightChild = t1->leftChild;
    t1->leftChild = t;
    t->height = max(height(t->leftChild), height(t->rightChild)) + 1;
    t1->height = max(height(t1->rightChild), height(t)) + 1;
    t = t1;
}

// 右左旋转
template <class KeyType, class ValueType>
void AVL_tree<KeyType, ValueType>::RL(TreeNode<KeyType, ValueType> *&t) {
    LL(t->rightChild);
    RR(t);
}

#endif // AVL_TREE_AVLTREE_H