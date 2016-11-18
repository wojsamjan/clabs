/* 
    $Revision: 63 $
    $Date: 2005-11-22 00:07:25 +0100 (wto, 22 lis 2005) $
    $URL: http://manta.univ.gda.pl/svn/wb/labs/c/541-BST-Rozw/tree04.c $
 */

#include "BT.h"

/*        
            8    
           / \   
          5   9  
         / \     
        1   6    
*/

struct node* buildTree() {
  struct node* root=new_node(8);  
  root->left=new_node(5);
  root->right=new_node(9);
  root->left->left=new_node(1);
  root->left->right=new_node(6);
  return root;
}
