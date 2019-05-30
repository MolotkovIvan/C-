#include <iostream>
#include <vector>

using namespace std;
typedef unsigned long long int ull;

struct Node{
	ull value;
	int h;
	ull sum;
	int size;
	Node *l, *r;

	int getheight(Node* t) {
		return (t == nullptr) ? 0 : t->h;
	} 

	ull getsum(Node* t) {
		return (t == nullptr) ? 0 : t->sum;
	} 

	int getsize(Node* t) {
		return (t == nullptr) ? 0 : t->size;
	}
	
	Node(ull y): value(y), h(1), sum(y), size(1), l(nullptr), r(nullptr) {}

	Node(ull y, Node* left, Node* right): value(y), l(left), r(right) {
		h = max(getheight(left), getheight(right)) + 1;
		sum = (getsum(left) + getsum(right)) + y;
		size = (getsize(left) + getsize(right)) + 1;
	}
	
	Node(Node* v) {
		size = v->size, value = v->value;
		h = v->h, sum = v->sum;
		l = v->l; r = v->r;
	}
	
};

int height(Node* x) {
	return (x == nullptr) ? 0 : x->h;
}

ull sum(Node* x) {
	return (x == nullptr) ? 0 : x->sum;
}

int size(Node* x) {
	return (x == nullptr) ? 0 : x->size;
}

Node* single_rotate_right(Node* t) {
	return new Node(t->l->value, t->l->l, new Node(t->value, t->l->r, t->r));
} 

Node* single_rotate_left(Node* t) {
	return new Node(t->r->value, new Node(t->value, t->l, t->r->l), t->r->r);
}

Node* double_rotate_right(Node* t) {
	t->l = single_rotate_left(t->l);
	return single_rotate_right(t);
}

Node* double_rotate_left(Node* t) {
	t->r = single_rotate_right(t->r);
	return single_rotate_left(t);
}

Node* balance(Node* t) {
	if (height(t->l) == height(t->r) + 2) {
		if (height(t->l->l) == height(t->l->r) + 1) {
			t = single_rotate_right(t);
		} else if (height(t->l->l) + 1 == height(t->l->r)) {
			t = double_rotate_right(t);
		}
	} else if (height(t->r) == height(t->l) + 2) {
		if (height(t->r->r) == height(t->r->l) + 1) {
			t = single_rotate_left(t);
		} else if (height(t->r->r) + 1 == height(t->r->l)) {
			t = double_rotate_left(t);
		}
	}
	return t;
}

Node* add_tree(Node* t, int x, int y) {
	if (t == nullptr){
		return new Node(y);
	} 
	Node* ans;
	if (x <= size(t->l)) {
		ans = new Node(t->value, add_tree(t->l, x, y), t->r);
	} else {
		ans = new Node(t->value, t->l, add_tree(t->r, x - size(t->l) - 1, y));
	}
	ans = balance(ans);
	return ans;
}

Node* findMin(Node* t) {
	if (t == nullptr) {
		return nullptr;
	}
	while (t->l) {
		t = t->l;
	}
	return t;
}


Node* delete_tree(Node* t, int x) {
	if (t == nullptr) {
		return nullptr; 
	} 
	Node* ans;
	if (x < size(t->l)) {
		ans = new Node(t->value, delete_tree(t->l, x), t->r);
	} else if (x > size(t->l)) {
		ans = new Node(t->value, t->l, delete_tree(t->r, x - size(t->l) - 1));
	} else {
		if (t->l && t->r) {
			Node* next = findMin(t->r);
			swap(t->value, next->value);
			ans = new Node(t->value, t->l, delete_tree(t->r, x - size(t->l) - 1));
		} else if (t->l) {
			ans = new Node(t->l);
		} else if (t->r) {
			ans = new Node(t->r);
		} else {
			return nullptr;
		}
	}
	ans = balance(ans);
	return ans;
}

Node* merge(Node* l, Node* r) {
	if (l == nullptr || r == nullptr) return l ? l : r;
	if (l->h <= r->h) {
		r->l = merge(l, r->l);
		r->sum = sum(r->r) + sum(r->l) + r->value;
		r->h = max(height(r->r), height(r->l)) + 1;
		r->size = size(r->r) + size(r->l) + 1;
		r = balance(r);
		return r;
	} else {
		l->r = merge(l->r, r);
		l->sum = sum(l->r) + sum(l->l) + l->value;
		l->h = max(height(l->r), height(l->l)) + 1;
		l->size = size(l->r) + size(l->l) + 1;
		l = balance(l);
		return l;
	}
}

pair<Node*, Node*> split(Node* t, int x) {
	if (t == nullptr) return make_pair(nullptr, nullptr);
	pair<Node*, Node*> ans;
	if (x > size(t->l)) {
		ans = split(t->r, x - size(t->l) - 1);
		t = new Node(t->value, t->l, ans.first);
		t = balance(t);
		return make_pair(t, ans.second);
	} else {
		ans = split(t->l, x);
		t = new Node(t->value, ans.second, t->r);
		t = balance(t);
		return make_pair(ans.first, t);
	}
}

void print_tree(Node* v) {
	if (!v) return; 
	cout << v->value << " ";
	print_tree(v->l);
	print_tree(v->r);
} 
void print_tree2(Node* v) {
	if (!v) return; 
	print_tree2(v->l);
	cout << v->value << " ";
	print_tree2(v->r);
}

Node* build_tree(vector<ull>& a, int l, int r) {
	if (l == r) return nullptr;
	if (l == r - 1) return new Node(a[l]); 
	return new Node(a[(l+r)/2], build_tree(a, l, (l+r)/2), build_tree(a, (l+r)/2 + 1, r));
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	int n; cin >> n;
	vector<ull> initial_list(n);
	ull A, B, M;
	cin >> initial_list[0] >> A >> B >> M; 
	for (int i = 1; i < n; i++) {
		initial_list[i] = (A * initial_list[i-1] + B) % M;
	}
	Node* root = nullptr;
	root = build_tree(initial_list, 0, n);
//	for (int i = 0; i < n; i++) {
//		root = add_tree(root, i, initial_list[i]);
//	}
	
	int m; cin >> m;
	std::string cmd;
	for (int i = 0; i < m; i++) {
		cin >> cmd;
		if (cmd.compare("out") == 0) {
			int l, r; cin >> l >> r; l--;
			pair<Node*, Node*> a = split(root, l);
			pair<Node*, Node*> b = split(a.second, r - l);
			print_tree2(b.first); cout << "\n";
		} else if (cmd.compare("sum") == 0) {
			int l, r; cin >> l >> r; l--;
			pair<Node*, Node*> a = split(root, l);
			pair<Node*, Node*> b = split(a.second, r - l);
			cout << (b.first->sum) << "\n";
		} else if (cmd.compare("cpy") == 0) {
			int l, r, z; cin >> l >> r >> z; l--, r--;
			pair<Node*, Node*> a1 = split(root, l);
			pair<Node*, Node*> b1 = split(a1.second, z);

			pair<Node*, Node*> a2 = split(root, r);
			pair<Node*, Node*> b2 = split(a2.second, z);

			Node* ans1 = merge(a2.first, b1.first);
			root = merge(ans1, b2.second);
		}
	}
	return 0;
}

