# CommonSubsequences
QUARTERNARY TREES: FINDING COMMON SEQUENCES

This code is based on finding the longest common sequence between strings with a slight modification. We will simply find whether sequences of a fixed length are common among data sets.

In the original program we have a file named genome.txt which has 1,000,000,000 characters interchanging between a, g, c, and t which have been generated using a random string generator. The same generator was used in order to get the virus.txt file which holds 4 strings of length 100 characters which also vary between a, g, c, and t. We have since reduced the size of genoe.txt to a more reasonable size for demonstration purposes.

A Quarternary tree is created through the QTreeNode and QuarternaryTree class stored in QuarternaryTree.h header with functions located in QuarternaryTree.cpp. These files enable a tree with 4 roots to be constructed with pointers to each child node. The roots are based on the 4 letters a, g, c, and t which stand for each protein marker in a genome. One Quarternary tree must be created per protein marker as the root is taken as the first character in the sequence. 

An InsertNode() function takes a sequence as an input and by iterating through the sequence, will create a node by calling on a CreateNode() function if the next letter in the sequence does not already exist.

A Traverse() function then takes a sequence input and checks if the sequence exists on the tree. This is where we will compare virus sequences against our created trees.

A ComputeHeight() function returns the height of the tree, and the CountNodes () gives the total number of nodes existing on a tree. The height of the tree should be equal to the sequence length minus 1. (Similar to indexing because the 0th level is the 1st character in the sequence). 

User can input a single string of the set length to test if it exists if they like, and common subsequences from the tree are kept in a stack that can be output to the console if desired.

