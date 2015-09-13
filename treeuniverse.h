#ifndef TREEUNIVERSE_H
#define TREEUNIVERSE_H

class TreeNode;

class TreeUniverse {
    double generationCount;
    TreeNode *root;

public:
    TreeUniverse();

    void setBit(int x, int y);
    int getBit(int x, int y);

    void runStep();
};

#endif // TREEUNIVERSE_H
