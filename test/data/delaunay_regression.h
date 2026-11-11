namespace DelaunayRegression {
long long orient(pt a, pt b, pt c) {
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}
long long determinant(pt a, pt b, pt c, pt d) {
    long long ax=a.x-d.x, ay=a.y-d.y, bx=b.x-d.x, by=b.y-d.y, cx=c.x-d.x, cy=c.y-d.y;
    return (ax*ax+ay*ay)*(bx*cy-by*cx)
         - (bx*bx+by*by)*(ax*cy-ay*cx)
         + (cx*cx+cy*cy)*(ax*by-ay*bx);
}
vector<pt> hull(vector<pt> p) {
    sort(p.begin(),p.end(),[](pt a,pt b){return tie(a.x,a.y)<tie(b.x,b.y);});
    vector<pt> lo,hi;
    for(pt a:p){while(lo.size()>1&&orient(lo[lo.size()-2],lo.back(),a)<=0)lo.pop_back();lo.push_back(a);}
    reverse(p.begin(),p.end());
    for(pt a:p){while(hi.size()>1&&orient(hi[hi.size()-2],hi.back(),a)<=0)hi.pop_back();hi.push_back(a);}
    lo.pop_back();hi.pop_back();lo.insert(lo.end(),hi.begin(),hi.end());return lo;
}
void check(vector<pt> p) {
    auto boundary=hull(p);
    assert(boundary.size()>=3);
    auto triangles=delaunay(p);
    int boundary_points=0;
    for(pt a:p){
        bool on=false;
        for(int i=0;i<(int)boundary.size();++i){
            pt b=boundary[i],c=boundary[(i+1)%boundary.size()];
            on|=orient(b,c,a)==0&&min(b.x,c.x)<=a.x&&a.x<=max(b.x,c.x)
                                 &&min(b.y,c.y)<=a.y&&a.y<=max(b.y,c.y);
        }
        boundary_points+=on;
    }
    assert((int)triangles.size()==2*(int)p.size()-2-boundary_points);
    set<pair<long long,long long>> used;
    long long area=0,expected_area=0;
    for(int i=0;i<(int)boundary.size();++i){pt a=boundary[i],b=boundary[(i+1)%boundary.size()];expected_area+=a.x*b.y-a.y*b.x;}
    for(auto [a,b,c]:triangles){
        long long turn=orient(a,b,c);assert(turn!=0);area+=abs(turn);
        if(turn<0)swap(a,b);
        for(pt v:{a,b,c}){assert(find(p.begin(),p.end(),v)!=p.end());used.insert({v.x,v.y});}
        for(pt d:p)assert(determinant(a,b,c,d)<=0);
    }
    assert(used.size()==p.size());assert(area==abs(expected_area));
}
void run() {
    assert(in_circle(pt(0,0),pt(2,0),pt(0,2),pt(1,1)));
    assert(!in_circle(pt(0,0),pt(2,0),pt(0,2),pt(2,2)));
    assert(!in_circle(pt(0,0),pt(2,0),pt(0,2),pt(3,3)));
    check({{0,0},{3,0},{0,3},{1,1}});
    check({{0,0},{4,0},{4,4},{0,4},{2,0},{2,4},{2,2}});
    mt19937 rng(8675309);
    for(int tt=0;tt<1500;++tt){
        pt a(int(rng()%41)-20,int(rng()%41)-20),b(int(rng()%41)-20,int(rng()%41)-20);
        pt c(int(rng()%41)-20,int(rng()%41)-20),d(int(rng()%41)-20,int(rng()%41)-20);
        assert(in_circle(a,b,c,d)==(determinant(a,b,c,d)>0));
    }
    for(int tt=0;tt<300;++tt){
        set<pair<int,int>> unique;
        int n=3+rng()%22;
        while((int)unique.size()<n)unique.insert({int(rng()%41)-20,int(rng()%41)-20});
        vector<pt> p;for(auto [x,y]:unique)p.emplace_back(x,y);
        if(hull(p).size()<3){--tt;continue;}
        shuffle(p.begin(),p.end(),rng);check(p);
    }
}
}
