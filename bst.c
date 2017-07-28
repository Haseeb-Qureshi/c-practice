#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct intTreeNode {
  int val;
  struct intTreeNode* left;
  struct intTreeNode* right;
};

typedef struct intTreeNode IntTreeNode;
typedef void (*NodeCallback)(IntTreeNode*);

IntTreeNode* addVal(IntTreeNode** rootp, int val) {
  IntTreeNode* root = *rootp;
  if (!root) {
    IntTreeNode* node = malloc(sizeof(IntTreeNode));
    *node = (IntTreeNode) { .val = val };
    *rootp = node;
    return node;
  } else {
    if (val > root->val) {
      // right side
      if (root->right) {
        return addVal(&root->right, val);
      } else {
        root->right = malloc(sizeof(IntTreeNode));
        *(root->right) = (IntTreeNode) { .val = val };
        return root->right;
      }
    } else {
      // left side
      if (root->left) {
        return addVal(&root->left, val);
      } else {
        root->left = malloc(sizeof(IntTreeNode));
        *(root->left) = (IntTreeNode) { .val = val };
        return root->left;
      }
    }
  }
}

bool includeVal(IntTreeNode* root, int val) {
  if (!root) {
    return false;
  }

  if (root->val == val) {
    return true;
  }

  if (val < root->val) {
    return includeVal(root->left, val);
  } else {
    return includeVal(root->right, val);
  }
}

bool deleteVal(IntTreeNode** rootp, int val) {
  IntTreeNode* root = *rootp;
  if (!root) {
    return false;
  }

  if (val > root->val) {
    return deleteVal(&root->right, val);
  } else if (val < root->val) {
    return deleteVal(&root->left, val);
  }

  // delete self

  if (!root->left && !root->right) {
    free(*rootp);
    *rootp = 0;
  } else if (root->left) {
    root->val = root->left->val;
    deleteVal(&root->left, root->left->val);
  } else {
    root->val = root->right->val;
    deleteVal(&root->right, root->right->val);
  }
  return true;
}

void freeTree(IntTreeNode* root) {
  if (!root) {
    return;
  }

  freeTree(root->left);
  freeTree(root->right);
  free(root);
}

void printTreeNode(IntTreeNode* node) {
  printf("%d\n", node->val);
}

void each(IntTreeNode* root, NodeCallback cb) {
  if (!root) {
    return;
  }

  each(root->left, cb);
  cb(root);
  each(root->right, cb);
}

int main() {
  IntTreeNode* root = 0;
  int nums[10] = { 4, 2, 7, 5, 6, 1, 9, 12, 52, 3 };

  for (int i = 0; i < 10; i++) {
    addVal(&root, nums[i]);
  }
  each(root, printTreeNode);

  for (int i = 0; i < 10; i++) {
    deleteVal(&root, nums[i]);
  }

  printf("\n\n\n");

  each(root, printTreeNode);
}
