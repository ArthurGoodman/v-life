#include "treenodebase.h"
#include "treenode.h"

TreeNodeBase::TreeNodeBase(bool alive) {
    nw = ne = sw = se = 0;
    level = 0;
    this->alive = alive;
    population = alive ? 1 : 0;
}

TreeNodeBase::TreeNodeBase(TreeNode *nw, TreeNode *ne, TreeNode *sw, TreeNode *se) {
    this->nw = nw;
    this->ne = ne;
    this->sw = sw;
    this->se = se;

    level = nw->level + 1;
    population = nw->population + ne->population + sw->population + se->population;
    alive = population > 0;
}

TreeNode *TreeNodeBase::create(bool alive) {
    return new TreeNode(alive);
}

TreeNode *TreeNodeBase::create(TreeNode *nw, TreeNode *ne, TreeNode *sw, TreeNode *se) {
    return new TreeNode(nw, ne, sw, se);
}

TreeNode *TreeNodeBase::create() {
    return (new TreeNode(false))->emptyTree(3);
}

TreeNode *TreeNodeBase::setBit(int x, int y) {
    if (!level)
        return new TreeNode(true);

    int offset = 1 << (level - 2);

    if (x < 0)
        if (y < 0)
            return create(nw->setBit(x + offset, y + offset), ne, sw, se);
        else
            return create(nw, ne, sw->setBit(x + offset, y - offset), se);
    else if (y < 0)
        return create(nw, ne->setBit(x - offset, y + offset), sw, se);
    else
        return create(nw, ne, sw, se->setBit(x - offset, y - offset));
}

int TreeNodeBase::getBit(int x, int y) {
    if (!level)
        return alive ? 1 : 0;

    int offset = 1 << (level - 2);

    if (x < 0)
        if (y < 0)
            return nw->getBit(x + offset, y + offset);
        else
            return sw->getBit(x + offset, y - offset);
    else if (y < 0)
        return ne->getBit(x - offset, y + offset);
    else
        return se->getBit(x - offset, y - offset);
}

TreeNode *TreeNodeBase::emptyTree(int level) {
    if (!level)
        return create(false);

    TreeNode *n = emptyTree(level - 1);
    return create(n, n, n, n);
}

TreeNode *TreeNodeBase::expandUniverse() {
    TreeNode *n = emptyTree(level - 1);
    return create(create(n, n, n, nw), create(n, n, ne, n), create(n, sw, n, n), create(se, n, n, n));
}
