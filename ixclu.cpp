ll ixclu (ll num, ll lim) {
    vector<ll> p;
    for (ll i=2; i*i<=num; ++i)
        if (num % i == 0) {
            p.push_back (i);
            while (num % i == 0)
                num /= i;
        }
    if (num > 1)
        p.push_back (num);

    ll sum = 0;
    for (ll msk=1; msk<(1<<p.size()); ++msk) {
        ll mult = 1, bits = 0;
        for (ll i=0; i<(ll)p.size(); ++i)
            if (msk & (1<<i)) {
                ++bits;
                mult *= p[i];
            }

        ll cur = lim / mult;
        if (bits % 2 == 1)
            sum += cur;
        else
            sum -= cur;
    }

    return lim-sum;
}
