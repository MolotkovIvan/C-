#ifndef _HUFFMAN_H_INCLUDE
#define _HUFFMAN_H_INCLUDE

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <fstream>

class TreeNode {
public:
	TreeNode(){}
	~TreeNode(){}

	TreeNode(char c, int w) {
		word = c;
		weight = w;
		l = nullptr;
		r = nullptr;
	}
	
	TreeNode(std::string str, int w) {
		word = str;
		weight = w;
		l = nullptr;
		r = nullptr;
	}
	
	TreeNode(const TreeNode& t) {
		weight = t.weight;
		word = t.word;
		l = t.l;
		r = t.r;
	}
	
	~TreeNode(int x) {
//		std::cout << "node deleted\n";
		if (l != nullptr) {
			r->~TreeNode(x);
		}
		if (r != nullptr) {
			r->~TreeNode(x);
		}
	}

	TreeNode operator+(TreeNode& t) {
		TreeNode sum;
		sum.weight = weight + t.weight;
		sum.word += word;
		sum.word += t.word;
		return sum;
	}
	void print_word() {
		std::cout << word;
	}
	
	bool operator>(const TreeNode& t) const{
		return weight > t.weight;
	}
	std::string word;
	int weight;
	TreeNode *l, *r; 
};

class HuffmanTree {
public:
	HuffmanTree() {}
	~HuffmanTree() {
		root->~TreeNode(1);
	}
	void encrypt(std::string cur, TreeNode *t) {
		if (t == nullptr) {
			return;
		}
		if (t->r == nullptr && t->l == nullptr) {
			code[t->word[0]] = cur;
		} else {
			if (t->l != nullptr) {
				encrypt(cur + "0", t->l);
			}
			if (t->r != nullptr) {
				encrypt(cur + "1", t->r);			
			}
		}
	}
	
	void build_tree() {
		for (std::map<char, int>::iterator i = begin(frequency); i != end(frequency); ++i) {
			TreeNode tree(i->first, i->second);
			heap.push(tree);
		}
		if (heap.size() == 1) {
			code[heap.top().word[0]] = '0';			
		} else {		
			while (heap.size() >= 2) {
				TreeNode *a = new TreeNode(heap.top());
				heap.pop();
				TreeNode *b = new TreeNode(heap.top());
				heap.pop();
				TreeNode new_node(*a + *b);
				new_node.l = a;
				new_node.r = b;
				heap.push(new_node);
			}
			root = new TreeNode(heap.top());
			heap.pop();
			encrypt(std::string(), root);
		}
	}
	
	void show_tree() {
		for (std::map<char, std::string>::iterator i = begin(code); i != end(code); ++i) {
			std::cout << i->first << " " << i->second << "\n";
		}
	}
	
	std::map<char, std::string>* get_table() {
		return &code;
	}

	void add_element(char e) {
		frequency[e] += 1;
	}
private:
	std::map<char, int> frequency;
	std::priority_queue<TreeNode, std::vector<TreeNode>, std::greater<TreeNode> > heap;
	std::map<char, std::string> code;
	TreeNode *root;
};

class HuffmanArchiver {
public:

	HuffmanArchiver(std::vector<char>& in, std::map<char, std::string>* c, std::ofstream& out): fin(in), code(c), fout(out) {}

	void write_table() {
		int length = 0;
		for (std::size_t i = 0; i < fin.size(); i++) {
			length += (*code)[fin[i]].size();
		}
		fout << (*code).size() << "\n";
		for (std::map<char, std::string>::iterator i = begin(*code); i != end(*code); ++i) {
			fout << i->first << i->second << "\n";
		}		
		fout << length << "\n";
	}

	void print() {
		write_table();
		int pos = 0;
		unsigned char buffer = 0;
		for (std::size_t i = 0; i < fin.size(); i++) {
			std::string c = (*code)[fin[i]];
			for (std::size_t j = 0; j < c.size(); j++) {
				if (c[j] == '1') {
					buffer |= (1 << pos);
				}
				pos++;
				if (pos == 8) {
					fout << buffer;
					buffer = 0;
					pos = 0;
				}
			}	
		}
		if (pos != 0) {
			fout << buffer;
		}
	}
	
	std::vector<char> fin;
	std::map<char, std::string> *code;
	std::ofstream& fout;
};

class HuffmanDecoder {
public:
	HuffmanDecoder(std::ofstream& out, std::ifstream& in): fout(out), fin(in) {}

	void make_table() {
		fin >> length;
		char c;
		fin.read(&c, sizeof(char));

		for (int i = 0; i < length; i++) {
			std::string str;
			fin.read(&c, sizeof(char));
			getline(fin, str, '\n');
			code[str] = c;
		}
	}
	
	void print() {
		make_table();
		std::string buffer;
		int len;
		fin >> len;
		char c;
		fin.read(&c, sizeof(char));
		int l = 0;
		while (!fin.eof()) {
			fin.read(&c, sizeof(char));
			for (int i = 0; i < 8 && l < len; i++) {
				buffer += c & (1 << i) ? '1' : '0'; 
				l++;
				if (code.find(buffer) != end(code)) {
					fout << code[buffer];
					buffer.clear();
				}				
			}
		}
	}
	int length;
	std::ofstream& fout;
	std::ifstream& fin;
	std::map<std::string, char> code;
};

#endif
