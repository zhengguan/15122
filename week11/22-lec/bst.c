#include "bst.h"
#include "stdbool.h"
#include "math.h"
#include "../21-code/lib/xalloc.h"
#include "../21-code/lib/contracts.h"

/* client provided */
//int elem_compare(elem e1, elem e2);


/* interface */
bst bst_new();
void bst_insert(bst B, elem x);
elem bst_lookup(bst B, elem x);


/**************************/
/* Library implementation */
/**************************/


/******** Predicates *****/
int height(tree *T) {
  return T == NULL ? 0 : T->height;
}

bool is_ordered(tree* T, elem lower, elem upper, bst B) {
  if (T == NULL) return true;
  return T->data != NULL
    && (lower == NULL || B->elem_compare(lower, T->data) < 0)
    && (upper == NULL || B->elem_compare(T->data, upper) < 0)
    && is_ordered(T->left, lower, T->data, B)
    && is_ordered(T->right, T->data, upper, B);
}

bool is_specified_height(tree* T) {
  if (T == NULL) return true;
  int computed_height =
    height(T->left) > height(T->right)
    ? height(T->left) + 1
    : height(T->right) + 1;
  return computed_height == T->height
    && is_specified_height(T->left)
    && is_specified_height(T->right);
}

bool is_balanced(tree* T) {
  if (T == NULL) return true;
  return abs(height(T->left) - height(T->right)) <= 1
    && is_balanced(T->left) && is_balanced(T->right);
}

bool is_tree(tree* T, bst B) {
  return is_ordered(T, NULL, NULL, B)
    && is_specified_height(T)
    && is_balanced(T);
}

bool is_bst(bst B) {
  return B != NULL && is_tree(B->root, B);
}


/******** Operations *****/
bst bst_new(elem_compare_fn* cmp)
{
  bst B = xmalloc(sizeof(struct bst_header));
  B->root = NULL;
  B->elem_compare = cmp;
  return B;
}

/******** lookup related functions *****/
elem tree_lookup(tree* T, elem x, bst B)
{
  REQUIRES(is_tree(T, B));

  if (T == NULL) return NULL;
  int r = B->elem_compare(x, T->data);
  if (r == 0) {
    return T->data;
  } else if (r < 0) {
    return tree_lookup(T->left, x, B);
  } else {
    return tree_lookup(T->right, x, B);
  }
}

elem bst_lookup(bst B, elem x)
{
  REQUIRES(is_bst(B) && x != NULL);

  elem r = tree_lookup(B->root, x, B);

  ENSURES(r == NULL || B->elem_compare(r, x) == 0);
  return r;
}

/******** insert related functions *****/
static inline int max(int a, int b)
{
  return (a > b) ? a : b;
}

// GIVNE: a tree T whose left and right subtrees are legal tree
// EFFECT: fix T's height value
void fix_height(tree* T, bst B) {
  REQUIRES(is_tree(T->left, B) && is_tree(T->right, B));
  T->height = max(height(T->left), height(T->right)) + 1;
  return;
}

// GIVNE: a tree T whose left and right subtrees are legal trees
// EFFECT: rotate T to the left size
// RETURNS: the rotated tree
tree* rotate_left(tree* T, bst B) {
  REQUIRES(T != NULL && T->right != NULL);
  REQUIRES(is_tree(T->left, B));
  REQUIRES(is_tree(T->right, B));

  tree* R = T->right;
  T->right = R->left;
  R->left = T;
  fix_height(T, B);
  fix_height(R, B);

  ENSURES(is_tree(R, B));
  return R;
}

// GIVNE: a tree T whose left and right subtrees are legal trees
// EFFECT: rotate T to the right side
// RETURNS: the rotated tree
tree* rotate_right(tree* T, bst B) {
  REQUIRES(T != NULL && T->left != NULL);
  REQUIRES(is_tree(T, B));
  REQUIRES(is_tree(T, B));

  tree* L = T->left;
  T->left = L->right;
  L->right = T;
  fix_height(T, B);
  fix_height(L, B);

  ENSURES(is_tree(L, B));
  return L;
}

// GIVEN: a tree that has just been inserted a node in its left subtree
// EFFECT: rebalance the given tree
// RETURNS: the tree after balanced
tree* rebalance_left(tree* T, bst B)
{
  REQUIRES(T != NULL && T->left != NULL);
  REQUIRES(is_tree(T->left, B) && is_tree(T->right, B));

  if (height(T->left) - height(T->right) == 2) {
    ASSERT(height(T->left->right) != height(T->left->left));

    if (height(T->left->left) > height(T->left->right)) {
      T = rotate_right(T, B);
    } else {
      T->left = rotate_left(T->left, B);
      T = rotate_right(T, B);
    }
  } else {
    fix_height(T, B);
  }

  ENSURES(is_tree(T, B));
  return T;
}

// GIVEN: a tree that has just been inserted a node in its right subtree
// EFFECT: rebalance the new tree
// RETURNS: the tree after balanced
tree* rebalance_right(tree* T, bst B)
{
  REQUIRES(T != NULL);
  REQUIRES(T->right != NULL);

  if (height(T->right) - height(T->left) == 2) {
    ASSERT(height(T->right->right) != height(T->right->left));

    if (height(T->right->right) > height(T->right->left)) {
      T = rotate_left(T, B);
    } else {
      T->right = rotate_right(T->right, B);
      T = rotate_left(T, B);
    }
  } else {
    fix_height(T, B);
  }

  ENSURES(is_tree(T, B));
  return T;
}


tree* tree_insert(tree* T, elem x, bst B)
{
  REQUIRES(is_tree(T, B));
  REQUIRES(x != NULL);

  if (T == NULL) {
    T = xmalloc(sizeof(tree));
    T->height = 1;
    T->data = x;
    T->left = NULL;
    T->right = NULL;
  } else {
    int r = B->elem_compare(x, T->data);
    if (r == 0) {
      T->data = x;
    } else if (r < 0) {
      T->left = tree_insert(T->left, x, B);
      T = rebalance_left(T, B);
    } else {
      T->right = tree_insert(T->right, x, B);
      T = rebalance_right(T, B);
    }
  }

  ENSURES(is_tree(T, B));
  return T;
}

void bst_insert(bst B, elem x)
{
  REQUIRES(is_bst(B));
  REQUIRES(x != NULL);

  B->root = tree_insert(B->root, x, B);

  ENSURES(is_bst(B));
  return;
}
