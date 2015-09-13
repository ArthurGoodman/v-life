#ifndef TREENODEBASE_H
#define TREENODEBASE_H

class TreeNode;

class TreeNodeBase {
    friend class TreeUniverse;

protected:
    TreeNode *nw, *ne, *sw, *se;
    int level;
    bool alive;
    double population;

public:
    TreeNodeBase(bool alive);
    TreeNodeBase(TreeNode *nw, TreeNode *ne, TreeNode *sw, TreeNode *se);

    TreeNode *create(bool alive);
    TreeNode *create(TreeNode *nw, TreeNode *ne, TreeNode *sw, TreeNode *se);

    static TreeNode *create();

    TreeNode *setBit(int x, int y);
    int getBit(int x, int y);

    TreeNode *emptyTree(int level);

    TreeNode *expandUniverse();
};

#endif // TREENODEBASE_H
