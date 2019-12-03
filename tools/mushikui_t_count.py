for i in range(5):
    with open("../data/dat{}_in".format(i)) as f:
        t = f.readline()
        m = {}
        print("虫食い t")
        for ch in t:
            if ch not in m:
                m[ch] = 0
            m[ch] += 1
        for ch in ["a", "b", "c", "d", "x"]:
            if ch not in m:
                m[ch] = 0
            print("{}: {} => {}%".format(ch, m[ch], m[ch] / len(t) * 100))