#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class UnionFind {
public:
	virtual ~UnionFind() = default;
	virtual void union_op(const string& a, const string& b) = 0; 
	virtual size_t find_op(const string& a) const = 0;
	virtual size_t size_op(const string& a) const = 0;
};

class SimpleUnionFind: public UnionFind {

	vector<size_t> val_to_parent;
	vector<size_t> set_sizes;
	unordered_map<string, size_t> val_to_loc;

public:
	void union_op(const string& a, const string& b) override {
		if (!val_to_loc.contains(a)) {
			val_to_parent.push_back(val_to_parent.size());
			set_sizes.push_back(1);
			val_to_loc[a] = val_to_parent.size() - 1;
			
		}
		if (!val_to_loc.contains(b)) {
			val_to_parent.push_back(val_to_parent.size());
			set_sizes.push_back(1);
			val_to_loc[b] = val_to_parent.size() - 1;
		}
		size_t a_root = find_op(a);
		size_t b_root = find_op(b);
		
		if (a_root == b_root) return;
		
		val_to_parent[a_root] = b_root;
		
		set_sizes[b_root] += set_sizes[a_root];
	}

	size_t find_op(const string& a) const override {
		if (!val_to_loc.contains(a)) {
			throw exception();
		}
		size_t p_loc = val_to_loc.at(a);
		while (val_to_parent[p_loc] != p_loc) {
			p_loc = val_to_parent[p_loc];
		}
		return p_loc;

	}

	size_t size_op(const string& a) const override {
		if (!val_to_loc.contains(a)) {
			throw exception();
		}
		return set_sizes[val_to_loc.at(a)];
	}
};