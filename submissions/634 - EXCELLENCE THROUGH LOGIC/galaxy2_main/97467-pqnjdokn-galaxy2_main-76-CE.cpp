
int query(int c1, int s1, int c2, int s2) {
    int idx = 0;
    int answer = INF;

    while (idx != -1) {
        Node &nd = tree[idx];

        answer = min(
            answer,
            getDistance(idx, c1, s1, c2, s2)
        );

        int mid = nd.mid;

        if (c1 == mid || c2 == mid)
            break;

        if (c1 < mid && c2 < mid) {
            idx = nd.left;
        }
        else if (c1 > mid && c2 > mid) {
            idx = nd.right;
        }
        else {
            break;
        }
    }

    return answer;
}
