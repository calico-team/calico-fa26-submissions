#include <bits/stdc++.h>
#include <cassert>
#include <ext/pb_ds/assoc_container.hpp>

namespace wala {

template <typename T> void setmin(T& a, const T& b) { if (b < a) a = b; }
template <typename T> void setmax(T& a, const T& b) { if (b > a) a = b; }

template <typename T> using min_pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template <typename T> using max_pq = std::priority_queue<T>;

struct splitmix64_hash {
	static uint64_t splitmix64(uint64_t x) {
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}
	size_t operator()(uint64_t x) const {
		static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}
};

template <typename K, typename V, typename Hash = splitmix64_hash>
using hash_map = __gnu_pbds::gp_hash_table<K, V, Hash>;

template <typename K, typename Hash = splitmix64_hash>
using hash_set = hash_map<K, __gnu_pbds::null_type, Hash>;

template <int MOD_> struct modnum {
	static constexpr int MOD = MOD_;
	static_assert(MOD_ > 0, "MOD must be positive");

private:
	using ll = long long;
	int v;

	static int minv(int a, int m) {
		a %= m;
		assert(a);
		return a == 1 ? 1 : int(m - ll(minv(m, a)) * ll(m) / a);
	}

public:
	modnum() : v(0) {}
	modnum(ll v_) : v(int(v_ % MOD)) { if (v < 0) v += MOD; }
	explicit operator int() const { return v; }
	friend std::ostream& operator << (std::ostream& out, const modnum& n) { return out << int(n); }
	friend std::istream& operator >> (std::istream& in, modnum& n) { ll v_; in >> v_; n = modnum(v_); return in; }
	friend bool operator == (const modnum& a, const modnum& b) { return a.v == b.v; }
	friend bool operator != (const modnum& a, const modnum& b) { return a.v != b.v; }

	modnum inv() const {
		modnum res;
		res.v = minv(v, MOD);
		return res;
	}
	modnum neg() const {
		modnum res;
		res.v = v ? MOD-v : 0;
		return res;
	}
	modnum operator- () const { return neg(); }
	modnum operator+ () const { return modnum(*this); }

	modnum& operator ++ () { if (++v == MOD) v = 0; return *this; }
	modnum& operator -- () { if (v == 0) v = MOD; --v; return *this; }
	modnum& operator += (const modnum& o) { v += o.v; if (v >= MOD) v -= MOD; return *this; }
	modnum& operator -= (const modnum& o) { v -= o.v; if (v < 0) v += MOD; return *this; }
	modnum& operator *= (const modnum& o) { v = int(ll(v) * ll(o.v) % MOD); return *this; }
	modnum& operator /= (const modnum& o) { return *this *= o.inv(); }

	friend modnum operator ++ (modnum& a, int) { modnum r = a; ++a; return r; }
	friend modnum operator -- (modnum& a, int) { modnum r = a; --a; return r; }
	friend modnum operator + (const modnum& a, const modnum& b) { return modnum(a) += b; }
	friend modnum operator - (const modnum& a, const modnum& b) { return modnum(a) -= b; }
	friend modnum operator * (const modnum& a, const modnum& b) { return modnum(a) *= b; }
	friend modnum operator / (const modnum& a, const modnum& b) { return modnum(a) /= b; }
};

template <typename T> T pow(T a, long long b) {
	assert(b >= 0);
	T r = 1;
	while (b) {
		if (b & 1) r *= a;
		b >>= 1;
		a *= a;
	}
	return r;
}

struct union_find {
	std::vector<int> par;
	union_find() {}
	union_find(int N) : par(N, -1) {}
	int get_par(int a) {
		while (par[a] >= 0) {
			if (par[par[a]] >= 0) par[a] = par[par[a]];
			a = par[a];
		}
		return a;
	}
	bool merge(int a, int b) {
		a = get_par(a), b = get_par(b);
		if (a == b) return false;
		if (par[a] > par[b]) std::swap(a, b);
		par[a] += par[b];
		par[b] = a;
		return true;
	}
	bool merge(std::array<int, 2> a) { return merge(a[0], a[1]); }
};

}

namespace wala {

struct binary_trie {
	struct node {
		int ch[2] = {0, 0};
	};
	std::vector<node> nodes;
	binary_trie() : nodes(1) {}
	void reserve(int n) { nodes.reserve(n); }
	void reset() { nodes.resize(1); }
	int new_root() {
		nodes.push_back({});
		return int(nodes.size())-1;
	}
	void add(int root, int x) {
		int cur = root;
		for (int b = 29; b >= 0; b--) {
			int z = (x >> b) & 1;
			if (!nodes[cur].ch[z]) {
				nodes[cur].ch[z] = int(nodes.size());
				nodes.push_back({});
			}
			cur = nodes[cur].ch[z];
		}
	}
	int insert(int root, int x) {
		int res = int(nodes.size());
		nodes.push_back(nodes[root]);
		int cur = res, prv = root;
		for (int b = 29; b >= 0; b--) {
			int z = (x >> b) & 1;
			int old = nodes[prv].ch[z];
			int nxt = int(nodes.size());
			nodes.push_back(nodes[old]);
			nodes[cur].ch[z] = nxt;
			cur = nxt;
			prv = old;
		}
		return res;
	}
	int max_xor(int root, int x) const {
		int res = 0, cur = root;
		for (int b = 29; b >= 0; b--) {
			int z = (x >> b) & 1;
			int nxt = nodes[cur].ch[z^1];
			if (nxt) {
				res |= 1 << b;
				cur = nxt;
			} else {
				cur = nodes[cur].ch[z];
			}
			assert(cur);
		}
		return res;
	}
};

}

namespace std {

template <class Fun>
class y_combinator_result {
	Fun fun_;
public:
	template <class T>
	explicit y_combinator_result(T&& fun) : fun_(std::forward<T>(fun)) {}
	template <class... Args>
	decltype(auto) operator()(Args&&... args) {
		return fun_(std::ref(*this), std::forward<Args>(args)...);
	}
};

template <class Fun>
decltype(auto) y_combinator(Fun&& fun) {
	return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

}

template <typename T, int NDIMS> struct tensor_view {
	static_assert(NDIMS >= 0, "NDIMS must be nonnegative");

protected:
	std::array<int, NDIMS> shape;
	std::array<int, NDIMS> strides;
	T* data;
	tensor_view(std::array<int, NDIMS> shape_, std::array<int, NDIMS> strides_, T* data_) : shape(shape_), strides(strides_), data(data_) {}

public:
	tensor_view() : shape{0}, strides{0}, data(nullptr) {}

protected:
	int flatten_index(std::array<int, NDIMS> idx) const {
		int res = 0;
		for (int i = 0; i < NDIMS; i++) res += idx[i] * strides[i];
		return res;
	}
	int flatten_index_checked(std::array<int, NDIMS> idx) const {
		int res = 0;
		for (int i = 0; i < NDIMS; i++) {
			assert(0 <= idx[i] && idx[i] < shape[i]);
			res += idx[i] * strides[i];
		}
		return res;
	}

public:
	T& operator[] (std::array<int, NDIMS> idx) const { return data[flatten_index(idx)]; }
	T& at(std::array<int, NDIMS> idx) const { return data[flatten_index_checked(idx)]; }

	template <int D = NDIMS>
	std::enable_if_t<(0 < D), tensor_view<T, NDIMS-1>> operator[] (int idx) const {
		std::array<int, NDIMS-1> nshape; std::copy(shape.begin()+1, shape.end(), nshape.begin());
		std::array<int, NDIMS-1> nstrides; std::copy(strides.begin()+1, strides.end(), nstrides.begin());
		return tensor_view<T, NDIMS-1>(nshape, nstrides, data + strides[0]*idx);
	}
	template <int D = NDIMS>
	std::enable_if_t<(0 < D), tensor_view<T, NDIMS-1>> at(int idx) const {
		assert(0 <= idx && idx < shape[0]);
		return operator[](idx);
	}
	template <int D = NDIMS>
	std::enable_if_t<(0 == D), T&> operator * () const { return *data; }

	template <typename U, int D> friend struct tensor_view;
	template <typename U, int D> friend struct tensor;
};

template <typename T, int NDIMS> struct tensor {
	static_assert(NDIMS >= 0, "NDIMS must be nonnegative");

protected:
	std::array<int, NDIMS> shape;
	std::array<int, NDIMS> strides;
	int len;
	T* data;

public:
	tensor() : shape{0}, strides{0}, len(0), data(nullptr) {}
	explicit tensor(std::array<int, NDIMS> shape_, const T& t = T()) {
		shape = shape_;
		len = 1;
		for (int i = NDIMS-1; i >= 0; i--) {
			strides[i] = len;
			len *= shape[i];
		}
		data = new T[len];
		std::fill(data, data+len, t);
	}
	tensor(const tensor& o) : shape(o.shape), strides(o.strides), len(o.len), data(new T[len]) {
		for (int i = 0; i < len; i++) data[i] = o.data[i];
	}
	tensor& operator=(tensor&& o) noexcept {
		using std::swap;
		swap(shape, o.shape);
		swap(strides, o.strides);
		swap(len, o.len);
		swap(data, o.data);
		return *this;
	}
	tensor(tensor&& o) : tensor() { *this = std::move(o); }
	tensor& operator=(const tensor& o) { return *this = tensor(o); }
	~tensor() { delete[] data; }

	using view_t = tensor_view<T, NDIMS>;
	view_t view() { return view_t(shape, strides, data); }
	operator view_t() { return view(); }
	using const_view_t = tensor_view<const T, NDIMS>;
	const_view_t view() const { return const_view_t(shape, strides, data); }
	operator const_view_t() const { return view(); }

	T& operator[] (std::array<int, NDIMS> idx) { return view()[idx]; }
	T& at(std::array<int, NDIMS> idx) { return view().at(idx); }
	const T& operator[] (std::array<int, NDIMS> idx) const { return view()[idx]; }
	const T& at(std::array<int, NDIMS> idx) const { return view().at(idx); }
	template <int D = NDIMS>
	std::enable_if_t<(0 < D), tensor_view<T, NDIMS-1>> operator[] (int idx) { return view()[idx]; }
	template <int D = NDIMS>
	std::enable_if_t<(0 < D), tensor_view<T, NDIMS-1>> at(int idx) { return view().at(idx); }
	template <int D = NDIMS>
	std::enable_if_t<(0 < D), tensor_view<const T, NDIMS-1>> operator[] (int idx) const { return view()[idx]; }
	template <int D = NDIMS>
	std::enable_if_t<(0 < D), tensor_view<const T, NDIMS-1>> at(int idx) const { return view().at(idx); }
	template <int D = NDIMS>
	std::enable_if_t<(0 == D), T&> operator * () { return *view(); }
	template <int D = NDIMS>
	std::enable_if_t<(0 == D), const T&> operator * () const { return *view(); }
};

int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(nullptr);
	int T; std::cin >> T;
	while (T--) {
		int N; std::cin >> N;
		std::vector<int> A(N); for (auto& a : A) { std::cin >> a; a--; }
		std::vector<int> V(N); for (auto& v : V) std::cin >> v;
		std::vector<std::vector<int>> rev(N);
		std::vector<int> deg(N, 0);
		for (int i = 0; i < N; i++) {
			rev[A[i]].push_back(i);
			deg[A[i]]++;
		}
		/* our graph is a functional graph so every component consists of a tree feeding into a cycle
		first remove all vertices with indegree 0 */
		std::vector<int> q; q.reserve(N);
		for (int i = 0; i < N; i++) if (deg[i] == 0) q.push_back(i);
		for (int i = 0; i < int(q.size()); i++) {
			int v = q[i];
			if (--deg[A[v]] == 0) q.push_back(A[v]);
		}
		// now we're only left with the cycles
		std::vector<bool> on_cycle(N);
		for (int i = 0; i < N; i++) on_cycle[i] = deg[i] > 0;
		std::vector<bool> seen(N, false);
		std::vector<int> ans(N);
		wala::binary_trie trie;
		trie.reserve(1 + 31*(N+1));
		for (int s = 0; s < N; s++) {
			if (!on_cycle[s] || seen[s]) continue;
			// solve the cycle
			std::vector<int> cyc;
			int cur = s;
			do {
				seen[cur] = true;
				cyc.push_back(cur);
				cur = A[cur];
			} while (cur != s);
			int L = int(cyc.size());
			std::vector<int> pref(L+1, 0);
			for (int i = 0; i < L; i++) pref[i+1] = pref[i] ^ V[cyc[i]];
			int cycle_xor = pref[L];
			trie.reset();
			int cyc_root = trie.new_root();
			for (int i = 0; i < L; i++) trie.add(cyc_root, pref[i]);
			int path_root = trie.insert(0, 0);
			struct state_t {
				int v, x, root;
			};
			std::vector<state_t> stk;
			for (int i = 0; i < L; i++) {
				int r = cyc[i], off = pref[i];
				ans[r] = std::max(
					trie.max_xor(cyc_root, off),
					trie.max_xor(cyc_root, off ^ cycle_xor)
				);
				for (int u : rev[r]) {
					if (!on_cycle[u]) stk.push_back({u, V[u], path_root});
				}
				while (!stk.empty()) {
					auto [v, x, root] = stk.back(); stk.pop_back();
					int best_tree = trie.max_xor(root, x);
					int best_cycle = std::max(
						trie.max_xor(cyc_root, x ^ off),
						trie.max_xor(cyc_root, x ^ off ^ cycle_xor)
					);
					ans[v] = std::max(best_tree, best_cycle);
					int nxt_root = trie.insert(root, x);
					for (int u : rev[v]) stk.push_back({u, x ^ V[u], nxt_root});
				}
			}
		} for (int i = 0; i < N; i++) std::cout << ans[i] << " \n"[i+1==N];
	}

	return 0;
}
