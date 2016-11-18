/* 
   $Revision: 54 $
   $URL: http://manta.univ.gda.pl/svn/wb/labs/c/540-BST/build123.c $
 */

#include <stdio.h>
#include <stdlib.h>
#include "build123.h"
#include "BT.h"


struct node* build123a(void) {
  struct node* root=new_node(2);
  struct node* lchild=new_node(1);
  struct node* rchild=new_node(3);

  root->left=lchild;
  root->right=rchild;
  return root;
}

struct node* build123b(void) {
  struct node* root=new_node(5);  
  root->left=new_node(4);
  root->right=new_node(6);
  return root;
}

struct node* build123c(void) {
  struct node* root=NULL;
  root=insert(root,8);
  root=insert(root,7);
  root=insert(root,9);
  return root;
}
