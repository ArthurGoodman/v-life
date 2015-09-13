#include "treenode.h"

TreeNode::TreeNode(bool alive)
    : TreeNodeBase(alive) {
}

TreeNode::TreeNode(TreeNode *nw, TreeNode *ne, TreeNode *sw, TreeNode *se)
    : TreeNodeBase(nw, ne, sw, se) {
}

TreeNode *TreeNode::oneGen(int bitmask) {
    if (!bitmask)
        return create(false);

    int self = (bitmask >> 5) & 1;

    bitmask &= 0x757;

    int n = 0;
    while (bitmask) {
        ++n;
        bitmask &= bitmask - 1;
    }

    return create(n == 3 || (n == 2 && self));
}

TreeNode *TreeNode::slowSimulation() {
    int allbits = 0;
    for (int y = -2; y < 2; ++y)
        for (int x = -2; x < 2; ++x)
            allbits = (allbits << 1) + getBit(x, y);
    return create(oneGen(allbits >> 5), oneGen(allbits >> 4), oneGen(allbits >> 1), oneGen(allbits));
}

TreeNode *TreeNode::centeredSubnode() {
    return create(nw->se, ne->sw, sw->ne, se->nw);
}

TreeNode *TreeNode::centeredHorizontal(TreeNode *w, TreeNode *e) {
    return create(w->ne->se, e->nw->sw, w->se->ne, e->sw->nw);
}

TreeNode *TreeNode::centeredVertical(TreeNode *n, TreeNode *s) {
    return create(n->sw->se, n->se->sw, s->nw->ne, s->ne->nw);
}

TreeNode *TreeNode::centeredSubSubnode() {
    return create(nw->se->se, ne->sw->sw, sw->ne->ne, se->nw->nw);
}

TreeNode *TreeNode::nextGeneration() {
    if (!population)
        return nw;
    if (level == 2)
        return slowSimulation();

    TreeNode *n00 = nw->centeredSubnode(),
             *n01 = centeredHorizontal(nw, ne),
             *n02 = ne->centeredSubnode(),
             *n10 = centeredVertical(nw, sw),
             *n11 = centeredSubSubnode(),
             *n12 = centeredVertical(ne, se),
             *n20 = sw->centeredSubnode(),
             *n21 = centeredHorizontal(sw, se),
             *n22 = se->centeredSubnode();

    return create(create(n00, n01, n10, n11)->nextGeneration(),
                  create(n01, n02, n11, n12)->nextGeneration(),
                  create(n10, n11, n20, n21)->nextGeneration(),
                  create(n11, n12, n21, n22)->nextGeneration());
}
