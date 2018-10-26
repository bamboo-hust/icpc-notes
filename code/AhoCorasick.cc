struct AhoCorasick {
	static const int ALPHABET_SIZE = 26;

	struct Node {
		Node* to[ALPHABET_SIZE];
		Node* fail;
		int ending_length; // 0 if is not ending

		Node() {
			for (int i = 0; i < ALPHABET_SIZE; ++i) to[i] = nullptr;
			fail = nullptr;
			ending_length = false;
		}
	};

	Node* root;

	void add(const string &s) {
		Node* cur_node = root;
		for (char c : s) {
			c -= 'a';
			if (!cur_node->to[c]) {
				cur_node->to[c] = new Node();
			}
			cur_node = cur_node->to[c];
		}
		cur_node->ending_length = s.size();
	}

	AhoCorasick(const vector<string> &a) {
		root = new Node();
		for (const string &s : a) add(s);

		queue<Node*> Q;
		root->fail = root;
		Q.push(root);

		while (!Q.empty()) {
			Node *par = Q.front(); Q.pop();
			for (int c = 0; c < ALPHABET_SIZE; ++c) {
				if (par->to[c]) {
					par->to[c]->fail = par == root ? root : par->fail->to[c];
					Q.push(par->to[c]);
				} else {
					par->to[c] = par == root ? root : par->fail->to[c]; 
				}
			}
		}
	}
};
