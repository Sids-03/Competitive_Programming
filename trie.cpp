template< int MXBIT> struct Trie{
    struct Node{
        int end_cnt = 0;
        int idx;
        int next[MXBIT] = {-1 , -1};
    };
    vector<Node>nodes;
    Node def;
    int k;
    Trie(int K){
        k = K;
        nodes.push_back(def);
    }

    void prints(){
        cout << nodes.size() << endl;
        for(int i = 0 ; i < nodes.size() ; i ++){
            cout << nodes[i].next[0] << " " << nodes[i].next[1] << endl;
        }
    }

    void add(string s , int id){
        int curr = 0;
        for(auto ch: s){
            if(nodes[curr].next[ch-'0'] == -1){
                nodes[curr].next[ch-'0'] = nodes.size();
                nodes.push_back(def);
            }
            curr = nodes[curr].next[ch-'0'];
        }
        nodes[curr].idx = id;
        nodes[curr].end_cnt++;
    }
    vector<int> dfs (string s){
        int x = 0 , curr = 0;
        int len = k-1;
        int ans = 0;
        for(auto ch: s){
            if(nodes[curr].next[ch-'0'] == -1){
                curr = nodes[curr].next[(ch-'0')^1];
            }else{
                if(ch == '0'){
                    x ^= (1<<len);
                }
                curr = nodes[curr].next[ch-'0'];
                ans ^= (1<<len);
            }
            --len;
        }
        int id = nodes[curr].idx;
        return {ans, x, id};

    }
};

// submission: https://codeforces.com/contest/1851/submission/215701055
