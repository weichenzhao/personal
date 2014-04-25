/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int maxDepth(TreeNode *root) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(root == NULL){
            return 0;
        }
        else{
            int left = maxDepth(root->left);
            int right = maxDepth(root->right);
            return left>right?left+1:right+1;
        }
    }
};
