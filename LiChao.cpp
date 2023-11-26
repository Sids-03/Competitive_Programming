 
struct Line {
  ll m, b;
  ll operator()(ll x) { return m * x + b; }
};
struct Node {
  Line seg;
  Node *lson, *rson;
  Node(Line _seg): seg(_seg), lson(0), rson(0) {} 
};
void insert(int l, int r, Line seg, Node* o) {
  if(l + 1 == r) {
    if(seg(l) < o->seg(l)) o->seg = seg;
    return;
  }
  int mid = (l + r) >> 1;
  if(seg.m < o->seg.m) swap(seg, o->seg);
  if(o->seg(mid) > seg(mid)) {
    swap(seg, o->seg);
    if(o->rson) insert(mid, r, seg, o->rson);
    else o->rson = new Node(seg);
  }
  else {
    if(o->lson) insert(l, mid, seg, o->lson);
    else o->lson = new Node(seg);
  }
}
ll query(int l, int r, int x, Node* o) {
  if(l + 1 == r) return o->seg(x);
  int mid = (l + r) >> 1;
  if(x < mid && o->lson) return min(o->seg(x), query(l, mid, x, o->lson));
  else if(o->rson) return min(o->seg(x), query(mid, r, x, o->rson));
  return o->seg(x);
}
void del(Node* o) {
  if(o->lson) del(o->lson);
  if(o->rson) del(o->rson);
  delete o;
}
void merge(Node* dest, Node* o) {
  if(o->seg.m != 0 || o->seg.b != inf) insert(-C, C, o->seg, dest);
  if(o->lson) merge(dest, o->lson);
  if(o->rson) merge(dest, o->rson);
}
 
