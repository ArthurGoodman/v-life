#ifndef TREENODE_H
#define TREENODE_H

#include "treenodebase.h"

class TreeNode : public TreeNodeBase {
public:
    TreeNode(bool alive);
    TreeNode(TreeNode *nw, TreeNode *ne, TreeNode *sw, TreeNode *se);

    TreeNode *oneGen(int bitmask);

    TreeNode *slowSimulation();

    TreeNode *centeredSubnode();

    TreeNode *centeredHorizontal(TreeNode *w, TreeNode *e);
    TreeNode *centeredVertical(TreeNode *n, TreeNode *s);

    TreeNode *centeredSubSubnode();

    TreeNode *nextGeneration();
};

#endif // TREENODE_H
