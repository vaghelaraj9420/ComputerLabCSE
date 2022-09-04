#include <stdio.h>

#include <stdlib.h>

#include <glpk.h>

#include <string.h>

int main()

{

//

    //........................................

  FILE *file = fopen("input.txt", "r");

  if (file == NULL) {
    perror("Unable to open file");
    exit(1);
  }

  int n, k;
  fscanf(file, "%d %d\n", &n, &k);

  // Collecting Durations...........
  int D[n];
  int value;
  int i = 0, j;
  while (fscanf(file, "%d", &value) == 1) {

    D[i] = value;
    i++;
    if (i == n)
      break;
  }
  for (i = 0; i < n; i++)
    printf(" %d", D[i]);

  // Filling F(i,i') values....
  int F[n + 1][n + 1], dependency[n + 1][n + 1];
  // initializing F(i,i') array with zeroes
  for (i = 0; i <= n; i++)
    for (j = 0; j <= n; j++)
      F[i][j] = 0;

  // initializing dependency[i][j] array with zeroes
  for (i = 0; i <= n; i++)
    for (j = 0; j <= n; j++)
      dependency[i][j] = 0;

  printf("\n");
  // taking inputs from the file
  char *token;
  char line[255];

  for (i = 0; i < n + 1; i++) {
    fgets(line, 255, file); // reading a line from file
    token =
        strtok(line, " "); // Identifying each token by passing a delimeter " "

    // Reading each token line by line and filling the dependency[i][j] array
    int value;
    while (token != NULL) {
      // printf(" %s  i: %d", token, i);
      printf(" %s", token);

      value = atoi(token);
      if (value == i) {
        j = 1;
      } else {
        dependency[i][j++] = value;
      }
      token = strtok(NULL, " "); // Moving on to next token
    }
  }
  printf("\n");
  // Printing dependency[i][j] array
  for (i = 1; i < n + 1; i++) {
    for (j = 1; j < n + 1; j++) {
      printf(" %d", dependency[i][j]);
    }
    printf("\n");
  }

  // Filling F(i, i') array using dependency array

  for (i = 1; i < n + 1; i++) {
    for (j = 1; j < n + 1; j++) {
      value = dependency[i][j];

      F[i][value] = 1;
    }
    printf("\n");
  }

  // Printing F(i, i') array
  for (i = 1; i < n + 1; i++) {
    for (j = 1; j < n + 1; j++) {
      printf(" %d", F[i][j]);
    }
    printf("\n");
  }

  fclose(file);
  //............................
  
    // Normal GLPK Program
    glp_prob *lp;

    int ia[1+1000], ja[1+1000];

    double ar[1+1000], z, x1, x2, x3;

   lp = glp_create_prob();

   glp_set_prob_name(lp, "sample");

   glp_set_obj_dir(lp, GLP_MIN);


   glp_add_rows(lp, 11);					// Change from here

   glp_set_row_name(lp, 1, "p");

   glp_set_row_bnds(lp, 1, GLP_UP, 0.0, 0.0);

   glp_set_row_name(lp, 2, "q");

   glp_set_row_bnds(lp, 2, GLP_UP, 0.0, 0.0);

   glp_set_row_name(lp, 3, "r");

    glp_set_row_bnds(lp, 3, GLP_UP, 0.0, 300.0);

    glp_add_cols(lp, 3);

    glp_set_col_name(lp, 1, "x1");

    glp_set_col_bnds(lp, 1, GLP_LO, 0.0, 0.0);

    glp_set_obj_coef(lp, 1, 10.0);

    glp_set_col_name(lp, 2, "x2");

    glp_set_col_bnds(lp, 2, GLP_LO, 0.0, 0.0);

    glp_set_obj_coef(lp, 2, 6.0);

    glp_set_col_name(lp, 3, "x3");

    glp_set_col_bnds(lp, 3, GLP_LO, 0.0, 0.0);

    glp_set_obj_coef(lp, 3, 4.0);

    ia[1] = 1, ja[1] = 1, ar[1] = 1.0; /* a[1,1] = 1 */

    ia[2] = 1, ja[2] = 2, ar[2] = 1.0; /* a[1,2] = 1 */

    ia[3] = 1, ja[3] = 3, ar[3] = 1.0; /* a[1,3] = 1 */

    ia[4] = 2, ja[4] = 1, ar[4] = 10.0; /* a[2,1] = 10 */

    ia[5] = 3, ja[5] = 1, ar[5] = 2.0; /* a[3,1] = 2 */

    ia[6] = 2, ja[6] = 2, ar[6] = 4.0; /* a[2,2] = 4 */

    ia[7] = 3, ja[7] = 2, ar[7] = 2.0; /* a[3,2] = 2 */

    ia[8] = 2, ja[8] = 3, ar[8] = 5.0; /* a[2,3] = 5 */

    ia[9] = 3, ja[9] = 3, ar[9] = 6.0; /* a[3,3] = 6 */

    glp_load_matrix(lp, 9, ia, ja, ar);

    glp_simplex(lp, NULL);

    z = glp_get_obj_val(lp);

    x1 = glp_get_col_prim(lp, 1);

    x2 = glp_get_col_prim(lp, 2);

    x3 = glp_get_col_prim(lp, 3);

    printf("\nz = %g; x1 = %g; x2 = %g; x3 = %g\n", z, x1, x2, x3);

    glp_delete_prob(lp);
    
     return 0;

}
