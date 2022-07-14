#ifndef ALGORITHMS_AND_DATA_STRUCTS_SPLAY_TREE_HPP
#define ALGORITHMS_AND_DATA_STRUCTS_SPLAY_TREE_HPP

template<class T>
class my_splay_tree {
private:
    struct __node {
        __node *__parent;
        __node *__left;
        __node *__right;
        T __data;
    };

private:

    __node *__find(const T &value, __node *node) noexcept {
        if (!node) return nullptr;
        else if (value > node->__data)
            return __find(value, node->__right);
        else if (value < node->__data)
            return __find(value, node->__left);
        return __splay(node);
    }

    void __zig(__node *node) noexcept {
        if (node == __root) return;
        __node *pivot = node->__parent;
        pivot->__left = node->__right;
        if (node->__right)
            node->__right->__parent = pivot;
        node->__parent = pivot->__parent;
        if (!pivot->__parent)
            __root = node;
        else if (pivot == pivot->__parent->__left)
            pivot->__parent->__left = node;
        else
            pivot->__parent->__right = node;
        node->__right = pivot;
        pivot->__parent = node;
    }

    void __zag(__node *node) noexcept {
        if (node == __root) return;
        __node *pivot = node->__parent;
        pivot->__right = node->__left;
        if (node->__left)
            node->__left->__parent = pivot;
        node->__parent = pivot->__parent;
        if (!pivot->__parent)
            __root = node;
        else if (pivot == pivot->__parent->__left)
            pivot->__parent->__left = node;
        else
            pivot->__parent->__right = node;
        node->__left = pivot;
        pivot->__parent = node;
    }

    void __insert(const T &value, __node *&parent, __node *&node) noexcept {
        if (!parent)
            parent = node;
        else if (value > parent->__data) {
            node->__parent = parent;
            __insert(value, parent->__right, node);
        } else {
            node->__parent = parent;
            __insert(value, parent->__left, node);
        }
        __splay(node);
    }

    void __destructor(__node *&node) noexcept {
        if (node) {
            __destructor(node->__left);
            __destructor(node->__right);
            delete node;
        }
    }

    __node *__splay(__node *&node) noexcept {
        while (node != __root) {
            if (node->__parent == __root && node == node->__parent->__left)
                __zig(node);
            else if (node->__parent == __root && node == node->__parent->__right)
                __zag(node);
            else if (node == node->__parent->__left && node->__parent == node->__parent->__parent->__left) {
                __zig(node->__parent);
                __zig(node);
            } else if (node == node->__parent->__right && node->__parent == node->__parent->__parent->__right) {
                __zag(node->__parent);
                __zag(node);
            } else if (node->__parent == node->__parent->__parent->__left && node == node->__parent->__right) {
                __zag(node);
                __zig(node);
            } else if (node->__parent == node->__parent->__parent->__right && node == node->__parent->__left) {
                __zig(node);
                __zag(node);
            }
        }
        return node;
    }

public:

    my_splay_tree() noexcept: __root(nullptr) {}

    ~my_splay_tree() noexcept {
        __destructor(__root);
    }

    __node *find(const T &value) noexcept {
        return __find(value, __root);
    }

    void insert(const T &value) noexcept {
        __node *node = new __node{nullptr, nullptr, nullptr, value};
        __insert(value, __root, node);
    }

private:
    __node *__root;
};

#endif //ALGORITHMS_AND_DATA_STRUCTS_SPLAY_TREE_HPP
