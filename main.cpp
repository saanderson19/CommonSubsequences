#include <fstream>
#include <vector>
#include <cstring>
#include "QuarternaryTree.h"
#include <string>
//#include <time.h> 
#include <iostream>

using namespace std;
bool get_reads(char * file_name, vector<string> &r, int vsize);
void checkinput(char input);
//void generator(char* file_name, int size);
//bool createFile(int vsize);

int main()
{
	cout << "This program will test if a virus subsequence exists on a given genome." << endl;
	cout << "We will begin using default genome and virus sequences as examples." << endl;
	cout << "You may specify the length of your genome and virus sequences you would like to test." << endl;
	cout << "Please specify you parameters now:" << endl;

	//initialization 
	int vsize = 0;
	int len = 0;
	char input;

	//set genome length
	cout << "How long of a genome sequence would you like to analyze? 1,000,000 is default." << endl;
	while (len < 1 || len > 1000000000) {
		cout << "Enter a valid genome length between 1 and 1 billion." << endl;
		cin >> len;
		cin.clear();
		cin.ignore(1000000000, '\n');
	}

	//set length of virus sequence and subsequent depth of tree
	cout << "How long of a virus sequence would like to analyze? 100 is default." << endl;
	while (vsize < 1 || vsize > 10000) {
		cout << "Enter a valid virus length between 1 and 1000." << endl;
		cin >> vsize;
		cin.clear();
		cin.ignore(1000000000, '\n');
	}

	cout << "We're loading up " << len << " characters into the tree, one moment please." << endl;

	//initialize quarternary tree
	QuarterTree a, g, c, t;

	ifstream in;
	in.open("genome.txt"); 
	if (!in.is_open()) {
		cout << "The read file could not be opened. Check the location.\t";
	}
	
	char * word = new char[vsize]; //char array for the genome
	
	word[vsize] = '\0'; //end of string indicator

	// insert the char array into the tree based on the root denoted by the first char

	for (int i = 1; i < (len - vsize -1); i++)   //read until the end of the file
	{
		for (int j = 0; j < (vsize - 1); j++) //limited our tree to sequences of 100 characters
			word[j] = word[j + 1];
		in >> word[(vsize - 1)];
		word[vsize] = '\0';
		if (i % (vsize - 1) == 0) //put sequences in the tree every time the char array reaches a length of 100 chars
		{
			if (word[0] == 'a')a.InsertNode(word); //same as above insert statement
			else if (word[0] == 'g')g.InsertNode(word);
			else if (word[0] == 'c')c.InsertNode(word);
			else if (word[0] == 't')t.InsertNode(word);
		}
	}
	
	in.clear();
	in.close(); //close genome file because we're through with it
	
	word = NULL;
	delete word; //clean up our pointer char array
	 
	cout << "Char 'a' tree height : " << a.ComputeHeight(a.Root) << " Char 'a' total nodes : " << a.CountNodes(a.Root) << endl;	
	cout << "Char 'g' tree height : " << g.ComputeHeight(g.Root) << " Char 'g' total nodes : " << g.CountNodes(g.Root) << endl;
	cout << "Char 'c' tree height : " << c.ComputeHeight(c.Root) << " Char 'c' total nodes : " << c.CountNodes(c.Root) << endl;
	cout << "Char 't' tree height : " << t.ComputeHeight(t.Root) << " Char 't' total nodes : " << t.CountNodes(t.Root) << endl;
	//something swanky using recursive calls so you can see the height and the total nodes in the tree

	//Testing virus sequences of user specified length from our example sets//

	vector<string> rds; //sets up vectors to hold reads from get_reads
	get_reads("virus.txt", rds, vsize); //puts reads in vector
	char *wo = new char[(vsize + 1)]; //temporary pointer char array
	for (int k = 0; k < rds.size(); k++) //loop for reads to be traversed and compared to words
	{
		cout << wo << endl;
		cout << wo[0];
		cout << "Testing sequence: " << rds[k] << endl;
		string rd = rds[k]; //turns vector into string
		strcpy_s(wo, (vsize + 1), rd.c_str()); //turns string into char * array
		if (wo[0] == 'a')a.TraverseTree(wo); //same as above insert but this time its just checking to see
		else if (wo[0] == 'g') g.TraverseTree(wo); //if that sequence exists in the created tree
		else if (wo[0] == 'c') c.TraverseTree(wo);
		else if (wo[0] == 't')t.TraverseTree(wo);
		else break;
	}

	cout << "Now that you've seen how it works, you may test your own sequence against our genome if you wish." << endl;

	//Testing user specfied sequence//
	char * test_sequence = new char[vsize]; //pointer char array for loading unique sequence
											//char input;
	string test = "";
	cout << "Would you like to test a specific virus sequence of length " << vsize << " ? Enter y or n." << endl;
	cin >> input;
	cin.ignore(100, '\n');
	checkinput(input); //checks if you said yes or no
	
	while (true) {
		if (input == 'y' || input == 'Y') {
			cout << "Note, only " << vsize << " characters will be accepted." << endl;
			cout << "Please enter virus sequence: " << endl;
			cin >> test; //gets test sequence thats inputted
			
			while (test.length() != vsize)
			{
				cout << "Please enter in a sequence of the right size : " << vsize << " characters" << endl;
				cin >> test; // if you mess up on length, here's another try
			}
			
			//make sure input is lowercase
			for (int k = 0; k < vsize; k++) {
				test[k] = tolower(test[k]);
			}

			strcpy_s(test_sequence, (vsize + 1), test.c_str()); // copies to pointer char array 
			
			if (test_sequence[0] == 'a') { (a.TraverseTree(test_sequence)); } //call traverse, checks for the roots 
			else if (test_sequence[0] == 'g') { g.TraverseTree(test_sequence); } // and then sees if a path exists
			else if (test_sequence[0] == 'c') { c.TraverseTree(test_sequence); }
			else if (test_sequence[0] == 't') { t.TraverseTree(test_sequence); }
		}
		cout << "Would you like to test another specific virus sequence of length " << vsize << " ? Enter y or n." << endl;
		cin >> input; // if you want to do it again, press y again.
		cin.ignore(100, '\n');
		checkinput(input);
		if (input == 'n' || input == 'N') { break; }
	}

	
	//We used a random generator to create our genome.txt and our virus.txt
	//In case you need your own, options provided here
	//there aren't really any safeties on this

	/*
	vector<string> rds2; //vector for file generation
	cout << "Would you like to generate your own file of size " << vsize << " ? Enter y or n." << endl;
	cin >> input;
	cin.ignore(100, '\n');
	checkinput(input);

	if (input == 'y') { createFile(vsize); }

	cout << "Would you like to generate another file of size " << vsize << " ? Enter y or n." << endl;
	cin >> input;
	cin.ignore(100, '\n');
	checkinput(input);
	*/
	
	delete wo;
	wo = NULL; // Nulls/deletes pointer
	
	system("pause");
	return true;
}

bool get_reads(char * file_name, vector<string> &r, int vsize) {
	//Modified to take in 100 characters and doesn't need an input value as a parameter
	ifstream in;
	in.open(file_name);
	if (!in.is_open()) {
		cout << "The read file could not be opened. Check the location.\t";
		return false;
	}
	char * word = new char[(vsize + 1)]; //looking for size of 100 characters from the virus2.txt file
	while (in.peek() != EOF)
	{
		in.getline(word, (vsize + 1), '\n'); //gets the line,puts it on a char array, shoves it into the vector
		r.push_back(word);
	}
	in.clear();
	in.close();
	
	word = NULL; //null and delete pointer
	delete word;
	
	return true;
}

void checkinput(char input) {
	while (input != 'y' && input != 'n' && input != 'Y' && input != 'N')
	{
		cout << "Enter y or n, please." << endl;
		cin >> input;
		cin.clear();
		cin.ignore(100, '\n');
	}
}

/*
char nuc_generator()
{
	int i;
	i = rand() % 4;
	if (i == 0) return char(97);
	if (i == 1) return  char(116);
	if (i == 2) return char(99);
	if (i == 3) return char(103);

}

void generator(char* file_name, int size, int number)
{
	//clock_t t;
	ofstream out;
	out.open(file_name);
	//srand(time(NULL));
	cout << "File of length " << size << " will be generated." << endl;
	//t = clock();
	for (int i = 0; i < number; i++ {
		for (int i = 0; i < size; i++)
		{
			out << nuc_generator();
		}
	}
	//t = clock() - t;
	//out << ((float)t / CLOCKS_PER_SEC) << " Seconds to generate file." << endl;

	out.clear();
	out.close();
	cout << "File " << file_name << "with << number << " sequences of length " << size << " has been generated." << endl;

}

bool createFile(int vsize) {
	char * file = new char[vsize];
	int number;
	
	cout << "What would you like to name your file? Format accepted, name.txt ." << endl;
	cin >> file;
	
	cout << How many sequences would you like in your file? << endl;
	cin >> number;
	
	generator(file, vsize, number); //calls generator function to generate you a file with your required name/size

	file = NULL;
	delete file;
	return true;
}
*/