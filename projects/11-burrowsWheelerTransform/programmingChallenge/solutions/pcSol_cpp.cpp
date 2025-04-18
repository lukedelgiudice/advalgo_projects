#include <bits/stdc++.h>

#define endln '\n'
#define print(x) cout << (x) << endln

using namespace std;
using ll = long long;

const int INF = INT_MAX - 1;
const ll LINF = LLONG_MAX - 1;

pair<vector<int>, map<int, int>> rankBwt(vector<int> &bw)
{
    /*
     * Given BWT array bw, return parallel list of B-ranks.
     * Also returns tots: map from value to # times it appears.
     */
    map<int, int> tots;
    vector<int> ranks;

    for (int val : bw)
    {
        ranks.push_back(tots[val]);
        tots[val]++;
    }
    return {ranks, tots};
}

map<int, pair<int, int>> firstCol(map<int, int> &tots)
{
    /*
     * Return map from value to the range of rows prefixed by that value
     */
    map<int, pair<int, int>> first;
    int totc = 0;
    for (const auto &[val, count] : tots)
    {
        first[val] = {totc, totc + count};
        totc += count;
    }
    return first;
}

vector<int> reverseBwt(vector<int> &bw)
{
    /*
     * Make original list from BWT list bw
     */
    pair<vector<int>, map<int, int>> rt = rankBwt(bw);
    vector<int> ranks = rt.first;
    map<int, int> tots = rt.second;
    map<int, pair<int, int>> first = firstCol(tots);
    int rowi = 0;
    int sentinel = -1;
    vector<int> t = {-1};
    while (bw[rowi] != sentinel)
    {
        int c = bw[rowi];
        t.push_back(c);
        rowi = first[c].first + ranks[rowi];
    }
    reverse(t.begin(), t.end());
    return t;
}

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    set<int> elements;
    for (int i = 0; i + 1 < n; i++)
    {
        if (arr[i] > 0)
        {
            elements.insert(arr[i]);
        }
    }
    int last = 0;
    vector<pair<int, int>> gaps;
    /*
     * From the sorted elements, get consecutive elements, and if there is a gap,
     * add it to our gaps array
     */
    for (int i : elements)
    {
        if (last + 1 <= i - 1)
        {
            // add 1 to the left, and subtract 1 to right to just get elements in between
            gaps.push_back({last + 1, i - 1});
        }
        gaps.push_back({i, i}); // # also make sure to check the elements in the actual array
        last = i;
    }
    int mx = 0;
    if (elements.size())
    {
        mx = *elements.rbegin();
    }
    if (k > mx)
    {
        // make sure to add a gap between largest element and K
        gaps.push_back({mx + 1, k});
    }
    int zero = find(arr.begin(), arr.end(), 0) - arr.begin();
    /*
     * Test each gap
     * If the element works, then we add to our answer the number of elements in
     * that gap, as all elements will work if one element works
     */
    int ans = 0;
    for (pair<int, int> item : gaps)
    {
        // cout << item.first << " " << item.second << endln;
        arr[zero] = item.first;
        vector<int> original = reverseBwt(arr);
        if (original.size() == arr.size())
        {
            // the original array is valid if there are no missing elements
            ans += item.second - item.first + 1;
        }
    }
    print(ans);
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
