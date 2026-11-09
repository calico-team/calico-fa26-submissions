 string solve(int N, int R, vector<int> A) {
    for(int i=0;i<A.size();i++) {
        if(A[i+1]-A[i]>=R) {
            return "Yes";
        }else{
      return "NO";
        }
    }
    return "";
}