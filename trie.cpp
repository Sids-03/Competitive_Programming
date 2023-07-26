template<int MXBIT> 
struct Trie{
    struct Node{
        int end_cnt = 0;
        int idx;
        int cnt[MXBIT];
        int next[MXBIT];
        Node(){
            for(int i = 0 ; i < MXBIT ; i ++) next[i] = -1 , cnt[i] = 0;
        }
    };
    vector<Node>nodes;
    Node def;
    int k;
    Trie(int K = 0){
        k = K;
        nodes.push_back(def);
    }

    void add(string s , int id){
        int curr = 0;
        for(auto ch: s){
            if(nodes[curr].next[ch-'0'] == -1){
                nodes[curr].next[ch-'0'] = nodes.size();
                nodes.push_back(def);
            }
            nodes[curr].cnt[ch-'0']++;
            curr = nodes[curr].next[ch-'0'];
        }
        nodes[curr].idx = id;
        nodes[curr].end_cnt++;
    }
    void del(string s){
        int curr = 0;
        for(auto ch: s){
            nodes[curr].cnt[ch-'0']--;
            curr = nodes[curr].next[ch-'0'];
        }
        nodes[curr].end_cnt--;
    }
    bool search(string word){
        int curr = 0;
        for(auto ch: word){
            if(nodes[curr].next[ch-'0'] == -1){
                return false;
            }else{
                curr = nodes[curr].next[ch-'0'];
            }
        }
        return (bool)nodes[curr].end_cnt;
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
    ll max_xor(string s){
        ll curr = 0 , ans = 0 , len = k-1;
        for(auto ch: s){
            if(nodes[curr].next[(ch-'0')^1] == -1 || nodes[curr].cnt[(ch-'0')^1] <= 0){
                curr = nodes[curr].next[ch-'0'];
            }else{
                curr = nodes[curr].next[(ch-'0')^1];
                ans ^= (1<<len);
            }
            --len;
        }
        return ans;
    }
};
//submission: https://codeforces.com/contest/1851/submission/215701055 
//submission2: https://leetcode.com/problems/word-break/submissions/1004336379/
//submission3: https://codeforces.com/contest/706/submission/215781306

