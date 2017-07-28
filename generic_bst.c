#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int (*Comparator)(void*, void*);

struct treeNode {
  void* val;
  struct treeNode* left;
  struct treeNode* right;
  Comparator cmp;
};

typedef struct treeNode TreeNode;
typedef void (*NodeCallback)(TreeNode*);

TreeNode* addVal(TreeNode** rootp, void* val, Comparator cmp) {
  TreeNode* root = *rootp;
  if (!root) {
    TreeNode* node = malloc(sizeof(TreeNode));
    *node = (TreeNode) { .val = val, .cmp = cmp };
    *rootp = node;
    return node;
  } else {
    if (cmp(val, root->val) > 0) {
      // right side
      if (root->right) {
        return addVal(&root->right, val, cmp);
      } else {
        root->right = malloc(sizeof(TreeNode));
        *(root->right) = (TreeNode) { .val = val, .cmp = cmp };
        return root->right;
      }
    } else {
      // left side
      if (root->left) {
        return addVal(&root->left, val, cmp);
      } else {
        root->left = malloc(sizeof(TreeNode));
        *(root->left) = (TreeNode) { .val = val, .cmp = cmp };
        return root->left;
      }
    }
  }
}

bool includeVal(TreeNode* root, void* val) {
  if (!root) {
    return false;
  }

  if (root->cmp(root->val, val) == 0) {
    return true;
  }

  if (root->cmp(val, root->val) < 0) {
    return includeVal(root->left, val);
  } else {
    return includeVal(root->right, val);
  }
}

bool _deleteVal(TreeNode** rootp, void* val, bool shouldFreeVal) {
  TreeNode* root = *rootp;
  if (!root) {
    return false;
  }

  if (root->cmp(val, root->val) > 0) {
    return _deleteVal(&root->right, val, shouldFreeVal);
  } else if (root->cmp(val, root->val) < 0) {
    return _deleteVal(&root->left, val, shouldFreeVal);
  }

  // delete self
  if (shouldFreeVal) {
    free(root->val);
    root->val = 0;
  }

  if (!root->left && !root->right) {
    free(*rootp);
    *rootp = 0;
  } else if (root->left) {
    root->val = root->left->val;
    _deleteVal(&root->left, root->left->val, false);
  } else {
    root->val = root->right->val;
    _deleteVal(&root->right, root->right->val, false);
  }
  return true;
}

bool deleteVal(TreeNode** rootp, void* val) {
  return _deleteVal(rootp, val, true);
}

void freeTree(TreeNode* root) {
  if (!root) {
    return;
  }

  freeTree(root->left);
  freeTree(root->right);
  free(root->val);
  free(root);
}

void printIntTreeNode(TreeNode* node) {
  printf("%d\n", *((int*) node->val));
}

void each(TreeNode* root, NodeCallback cb) {
  if (!root) {
    return;
  }

  each(root->left, cb);
  cb(root);
  each(root->right, cb);
}

int intCmp(void* p1, void* p2) {
  int x = *((int*) p1);
  int y = *((int*) p2);
  return x - y;
}

int main() {
  TreeNode* root = 0;
  int nums[10] = { 4, 2, 7, 5, 6, 1, 9, 12, 52, 3 };

  for (int i = 0; i < 10; i++) {
    int* nump = malloc(sizeof(int));
    *nump = nums[i];
    addVal(&root, (void*) nump, intCmp);
  }

  each(root, printIntTreeNode);

  for (int i = 0; i < 10; i++) {
    deleteVal(&root, (void*) (&nums[i]));
  }

  printf("\n\n\n");

  each(root, printIntTreeNode);
}
