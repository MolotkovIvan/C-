#include <bits/stdc++.h>

using namespace std;

struct Node{
	pair<int, int> v;
	int prior;
	int size;
	Node *l, *r, *p;

	Node(pair<int, int> x, int y): v(x), prior(y), size(1), l(nullptr), r(nullptr), p(nullptr) {}
};

int size(Node* t) {
	return t ? t->size : 0;
}

map<pair<int,int>, Node*> m;
vector<set<pair<int,int>>> allEdges;

void print_tree(Node* t) {
	if (t == nullptr) return;
	print_tree(t->l);
	cout << "(" << t->v.first << ", " << t->v.second << ") ";
	print_tree(t->r);
}

void update(Node* t) {
	if (!t) return;
	t->size = size(t->l) + size(t->r) + 1;
	if (t->l) t->l->p = t;
	if (t->r) t->r->p = t;
	if (t->p) {
		if (t->p->l != t && t->p->r != t) t->p = nullptr;
	}
}

Node* merge(Node* l, Node* r) {
	if (!l || !r) {
		return l ? l : r;
	} else if (l->prior > r->prior) {
		l->r = merge(l->r, r);
		update(l);
		return l;
	} else {
		r->l = merge(l, r->l);
		update(r);
		return r;
	}
}

void split(Node* t, Node*& l, Node*& r, int key) {
	if (!t) {
		l = r = 0;
		return;
	}
	if (key <= size(t->l)) {
		split(t->l, l, t->l, key); r = t;
		update(r);
	} else {
		split(t->r, t->r, r, key - size(t->l) - 1); l = t;
		update(l);
	}
	update(t);
}

void erase(Node*& t, int key) {
	if (!t) return;
	if (size(t->l) > key) {
		erase(t->l, key);
	} else if (size(t->l) < key) {
		erase(t->r, key);
	} else {
		t = merge(t->l, t->r);
	}
	update(t);
}

Node* getRoot(Node* t) {
	if (t == nullptr) return nullptr;
	if (t->p == nullptr) return t;
	return getRoot(t->p);
}

int getPosition(Node* t) {
	if (t == nullptr) return 0;
	int res = size(t->l);
	while (t->p != nullptr) {
		if (t->p->r == t) {
			res += size(t->p->l) + 1;
		}
		t = t->p;
	}
	return res;	
}

void rotate(Node* t, int x) {
	Node *l, *r;
	split(t, l, r, x);
	merge(r, l);
}

bool isConnected(int a, int b) {
	if (allEdges[a].size() == 0 || allEdges[b].size() == 0) {
		return false;
	} else {
		Node *pa = m[*allEdges[a].lower_bound(make_pair(a,0))];
		Node *pb = m[*allEdges[b].lower_bound(make_pair(b,0))];
//		cout << pa->v.first << " " << pa->v.second << "\n";
//		cout << pb->v.first << " " << pb->v.second << "\n";
//		print_tree(getRoot(pa)); cout << "\n";
//		print_tree(getRoot(pb)); cout << "\n";
		return getRoot(pa) == getRoot(pb);
	} 
}

void cut(int a, int b) {
	allEdges[a].erase(make_pair(a,b)), allEdges[b].erase(make_pair(b,a));
	Node* node1 = m[make_pair(a,b)];
	Node* node2 = m[make_pair(b,a)];
	int i = getPosition(node1), j = getPosition(node2);
	if (i > j) swap(i,j);
	Node *root = getRoot(node1), *a1, *b1, *c1;
	split(root, a1, b1, i);
	split(b1, b1, c1, j-i);
	erase(b1, 0), erase(c1, 0);
	/*print_tree(*/merge(a1, c1);/*); cout << "\n";*/
}

void link(int a, int b) {
	Node *pa, *pb;
	if (allEdges[a].size() == 0) {
		pa = nullptr;
	} else {
		pa = m[*allEdges[a].lower_bound(make_pair(a,0))];
	} 
	if (allEdges[b].size() == 0) {
		pb = nullptr;
	} else {
		pb = m[*allEdges[b].lower_bound(make_pair(b,0))];
	} 
	rotate(getRoot(pa), getPosition(pa));
	rotate(getRoot(pb), getPosition(pb));
	Node *e1 = new Node(make_pair(a, b), rand()), *e2 = new Node(make_pair(b, a), rand());
	m[make_pair(a, b)] = e1, m[make_pair(b, a)] = e2;
	allEdges[a].insert(make_pair(a,b)), allEdges[b].insert(make_pair(b,a));
	/*print_tree(*/merge(merge(getRoot(pa), e1), merge(getRoot(pb), e2));/*); cout << "\n";*/
}

int main() {
	srand(time(nullptr));
	int n, m; cin >> n >> m;
	allEdges.resize(n+1);
	string cmd;
	for (int i = 0; i < m; i++) {
		cin >> cmd;
		if (cmd.compare("link") == 0) {
			int a,b; cin >> a >> b;
			link(a,b);
		} else if (cmd.compare("cut") == 0) {
			int a, b; cin >> a >> b;
			cut(a,b);
		} else if (cmd.compare("get") == 0) {
			int a, b; cin >> a >> b;
			if (a == b) {
				cout << 1;
			} else {
				cout << (isConnected(a,b) ? 1 : 0);
			}
		}
	}
	cout << "\n";
	return 0;
}