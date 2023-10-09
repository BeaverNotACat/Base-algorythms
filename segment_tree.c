/*
 * This code is a segment tree template with explanations💀💀💀
 * Yes, codestyle is a mix of shitty python and shitty c++
 * Written with 💖 by @BeaverNotACat
 */
#include <stdio.h>

/* You can set up an optimal length of tree array
 * by mulplying input array lenght with 4
 * Also remember that this algo left first element of array empty
 */
int seg_tree[4096];

/*As i know there are no min and max for int*/
int max(int a, int b) {
  if (a > b)
    return a;
  return b;
}

int min(int a, int b) {
  if (a > b)
    return b;
  return a;
}
/*
 * arr - initial array
 * cur_index - index of the current tree point. Shuld be started with 1
 * l_border and r_border - borders of the arr segment to go in recursion
 * lr_mid = middle of the arr segment
 */
void build_tree(int arr[], int cur_index, int l_border, int r_border) {
  if (l_border == r_border) {
    seg_tree[cur_index] = arr[l_border]; /* Setting up the lowest layer */
  } else {
    /*
     * Reqursion shit go from the lowest layer
     * If you will try to do it by hand you will understand
     */
    int borders_mid = (l_border + r_border) / 2;
    build_tree(arr, cur_index * 2, l_border, borders_mid);
    build_tree(arr, cur_index * 2 + 1, borders_mid + 1, r_border);
    /* Operation that sets up the "type" of tree f.e. summ */
    seg_tree[cur_index] = seg_tree[cur_index * 2] + seg_tree[cur_index * 2 + 1];
  }
}

/*
 * Using builded tree
 * l_tree_border and r_tree_border - As l/r_border in build() used for reqursion
 * l and r - segment of innitial array to calculate
 */
int take_segment(int cur_index, int l_tree_border, int r_tree_border, int l,
                 int r) {
  printf("%d%c%d%c", l_tree_border, ' ', r_tree_border, '\n');
  printf("%d%c%d%s", l, ' ', r, "\n\n");
  if (l > r)
    return 0;
  if (l == l_tree_border && r == r_tree_border)
    return seg_tree[cur_index];
  int borders_mid = (l_tree_border + r_tree_border) / 2;
  return take_segment(cur_index * 2, l_tree_border, borders_mid, l,
                      min(r, borders_mid)) +
         take_segment(cur_index * 2 + 1, borders_mid + 1, r_tree_border,
                      max(l, borders_mid + 1), r);
}

int main() {
  int input_lenght, l, r; /* Amount of input numbers*/
  int arr[512];
  printf("%s", "Please enter array lenght: ");
  scanf("%d", &input_lenght);

  printf("%s", "Now enter array elemnts: ");
  for (int i = 0; i < input_lenght; ++i)
    scanf("%d", &arr[i]);

  build_tree(arr, 1, 0, input_lenght - 1);
  printf("%s", "Sengment tree sucsessfully created\n");

  while (1) {
    printf("%s", "Now you can specify segments: ");
    scanf("%d%d", &l, &r);
    printf("%d%c", take_segment(1, 0, input_lenght - 1, l - 1, r - 1), '\n');
  }
  return 0;
}
