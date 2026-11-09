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

} // namespace std

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

namespace wala {
struct interval_basis {
	int W;
	std::array<int, 30> piv{}, pmask{};
	std::vector<int> basis_idx, basis_pos, coef, free_idx, sig_id;
	std::vector<uint64_t> sig;
	std::vector<int> basis_class;
	interval_basis(const std::vector<int>& L, const std::vector<int>& R, int k, int W_)
		: W(W_), basis_pos(L.size(), -1), coef(L.size()), sig_id(L.size(), -1) {
		int N = int(L.size());
		for (int i = 0; i < N; i++) {
			int x = (L[i] ^ R[i]) >> k;
			int mask = 0;
			for (int b = W-1; b >= 0; b--) {
				if (((x >> b) & 1) == 0) continue;
				if (piv[b]) {
					x ^= piv[b];
					mask ^= pmask[b];
				} else {
					int g = int(basis_idx.size());
					piv[b] = x;
					pmask[b] = mask ^ (1 << g);
					basis_pos[i] = g;
					coef[i] = 1 << g;
					basis_idx.push_back(i);
					break;
				}
			}
			if (x == 0) {
				coef[i] = mask;
				free_idx.push_back(i);
			}
		}
		int rank = int(basis_idx.size());
		int F = int(free_idx.size());
		int words = (F + 63) / 64;
		sig.assign(size_t(rank) * words, 0);
		for (int j = 0; j < F; j++) {
			int i = free_idx[j];
			int mask = coef[i];
			while (mask) {
				int g = __builtin_ctz(unsigned(mask));
				mask &= mask-1;
				sig[size_t(g)*words + j/64] |= uint64_t(1) << (j%64);
			}
			sig_id[i] = j+1;
		}
		basis_class.resize(rank);
		for (int g = 0; g < rank; g++) {
			int cnt = 0, one = -1;
			for (int j = 0; j < words; j++) {
				uint64_t x = sig[size_t(g)*words+j];
				int pc = __builtin_popcountll(x);
				cnt += pc;
				if (pc) one = 64*j + __builtin_ctzll(x);
			}
			int c;
			if (cnt == 0) c = 0;
			else if (cnt == 1) c = one+1;
			else {
				c = F+g+1;
				for (int h = 0; h < g; h++) {
					if (std::equal(
						sig.begin()+size_t(g)*words,
						sig.begin()+size_t(g+1)*words,
						sig.begin()+size_t(h)*words
					)) {
						c = basis_class[h];
						break;
					}
				}
			}
			basis_class[g] = c;
			sig_id[basis_idx[g]] = c;
		}
	}

	bool solve(int target, int& mask) const {
		mask = 0;
		for (int b = W-1; b >= 0; b--) {
			if (((target >> b) & 1) == 0) continue;
			if (!piv[b]) return false;
			target ^= piv[b];
			mask ^= pmask[b];
		}
		return target == 0;
	}
	bool one_free(const std::vector<int>& a, const std::vector<int>& b, int mask) const {
		for (int i = 0; i < int(a.size()); i++) {
			int off = basis_pos[i] == -1 ? 0 : ((mask >> basis_pos[i]) & 1);
			if (a[i]+1 < b[i] && !(a[i]&1)) {
				int rhs = off;
				if (sig_id[i] != 0 || rhs == 0) return true;
			}
			if (a[i] < b[i]-1 && (b[i]&1)) {
				int rhs = 1 ^ off;
				if (sig_id[i] != 0 || rhs == 0) return true;
			}
		}
		return false;
	}
	bool two_free(const std::vector<int>& a, const std::vector<int>& b, int mask) const {
		std::vector<std::array<int, 2>> seen(a.size()+1, std::array<int, 2>{-1, -1});
		int first_class = -1;
		for (int i = 0; i < int(a.size()); i++) {
			int off = basis_pos[i] == -1 ? 0 : ((mask >> basis_pos[i]) & 1);
			for (int req = 0; req < 2; req++) {
				bool ok = req == 0 ? (a[i]+1 < b[i] && !(a[i]&1)) : (a[i] < b[i]-1 && (b[i]&1));
				if (!ok) continue;
				int rhs = req ^ off;
				int c = sig_id[i];
				if (c == 0 && rhs) continue;
				if (first_class == -1) first_class = c;
				else if (c != first_class) return true;
				if (seen[c][rhs] != -1 && seen[c][rhs] != i) return true;
				seen[c][rhs] = i;
			}
		}
		return false;
	}
}; // namespace ecnerwala

int solve_matcha(const std::vector<int>& L, const std::vector<int>& R) {
	int N = int(L.size());
	int ans = 0;
	for (int k = 29; k >= 0; k--) {
		int W = 30-k;
		std::vector<int> a(N), b(N);
		int base = 0;
		for (int i = 0; i < N; i++) {
			a[i] = L[i] >> k;
			b[i] = R[i] >> k;
			base ^= a[i];
		}
		interval_basis basis(L, R, k, W);
		int m0, m1;
		bool ok0 = basis.solve(base ^ (ans >> k), m0);
		if (ok0 && basis.one_free(a, b, m0)) {
			ans |= (1 << (k+1))-1;
			break;
		}
		bool ok1 = basis.solve(base ^ ((ans >> k) | 1), m1);
		if (ok1 && basis.two_free(a, b, m1)) {
			ans |= (1 << (k+1))-1;
			break;
		}
		if (ok1) ans |= 1 << k;
	}
	return ans;
}

}

int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(nullptr);
	int T; std::cin >> T;
	while (T--) {
		int N; std::cin >> N;
		std::vector<int> L(N); for (auto& x : L) std::cin >> x;
		std::vector<int> R(N); for (auto& x : R) std::cin >> x;
		std::cout << wala::solve_matcha(L, R) << '\n';
	}

	return 0;
}
