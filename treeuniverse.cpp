#include "treeuniverse.h"
#include "treenode.h"
#include <QDebug>

TreeUniverse::TreeUniverse() {
    generationCount = 0;
    root = TreeNode::create();
}

void TreeUniverse::setBit(int x, int y) {
    while (true) {
        int maxCoord = 1 << (root->level - 1);
        if (-maxCoord <= x && x <= maxCoord - 1 && -maxCoord <= y && y <= maxCoord - 1)
            break;
        root = root->expandUniverse();
    }

    root = root->setBit(x, y);
}

int TreeUniverse::getBit(int x, int y) {
    int maxCoord = 1 << (root->level - 1);

    if (-maxCoord > x || x > maxCoord - 1 || -maxCoord > y || y > maxCoord - 1)
        return -1;

    return root->getBit(x, y);
}

void TreeUniverse::runStep() {
    while (root->level < 3 ||
           root->nw->population != root->nw->se->se->population ||
           root->ne->population != root->ne->sw->sw->population ||
           root->sw->population != root->sw->ne->ne->population ||
           root->se->population != root->se->nw->nw->population)
        root = root->expandUniverse();

    root = root->nextGeneration();
    ++generationCount;
}
