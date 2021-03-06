
for i in range(5):
    with open("../data/dat{}_ref".format(i)) as f:
        print("data{}:".format(i))
        t = f.readline()
        t_len = len(t)
        m = {}
        it = iter(t)
        prev = ""
        for s in it:
            try:
                tmp = s # + next(it)
            except StopIteration:
                break
            if prev not in m:
                m[prev] = {}
            if tmp not in m[prev]:
                m[prev][tmp] = 0
            m[prev][tmp] += 1
            prev = tmp
        for prev, v in m.items():
            print(prev)
            sum = 0
            for cnt in v.values():
                sum += cnt
            for nxt, cnt in v.items():
                print("\t{}: {}%".format(nxt, cnt / sum * 100))
            
