//implementation of BSP partition of b-trees.
#include <stdio.h>
#include <stdlib.h>
#include<math.h>

#define DIMENSION 2

typedef struct BSPNode {
  double plane[DIMENSION];
  struct BSPNode *left;
  struct BSPNode *right;
} BSPNode;

void bsp_print(BSPNode *node) {
  if (node == NULL) {
    printf("(null)\n");
    return;
  }
  printf("Node: (%f, %f)\n", node->plane[0], node->plane[1]);
  printf("Left subtree:\n");
  bsp_print(node->left);
  printf("Right subtree:\n");
  bsp_print(node->right);
  
}

BSPNode *bsp_create(double points[][DIMENSION], size_t n) {
  if (n == 0) return NULL;

  size_t longest_dimension = 0;
  double longest_length = -1;
  for (size_t i = 0; i < n; i++) {
    double length = 0;
    for (size_t j = 0; j < DIMENSION; j++) {
      length += points[i][j] * points[i][j];
      length = sqrt(length);
    }
    if (length > longest_length) {
      longest_length = length;
      longest_dimension = i;
    }
  }

  BSPNode *node = malloc(sizeof(BSPNode));
  for (size_t i = 0; i < DIMENSION; i++) {
    node->plane[i] = points[longest_dimension][i];
  }

  size_t left_count = 0;
  size_t right_count = 0;
  double left_points[n][DIMENSION];
  double right_points[n][DIMENSION];
  for (size_t i = 0; i < n; i++) {
    if (i == longest_dimension) continue;
    if (points[i][longest_dimension] < node->plane[longest_dimension]) {
      for (size_t j = 0; j < DIMENSION; j++) {
        left_points[left_count][j] = points[i][j];
      }
      left_count++;
    } else {
      for (size_t j = 0; j < DIMENSION; j++) {
        right_points[right_count][j] = points[i][j];
      }
      right_count++;
    }
  }

  node->left = bsp_create(left_points, left_count);
  node->right = bsp_create(right_points, right_count);

  bsp_print(node);

  return node;
}



void bsp_free(BSPNode *node) {
  if (node == NULL) return;
  bsp_free(node->left);
  bsp_free(node->right);
  free(node);
}

int main() {
  double points[][DIMENSION] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
  size_t n = sizeof(points) / sizeof(points[0]);

  BSPNode *root = bsp_create(points, n);

  bsp_free(root);

  return 0;
}
