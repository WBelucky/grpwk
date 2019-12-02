for i in range(5):
    with open("../data/dat{}_ref".format(i)) as f:
        s = f.readline()
        s_len = len(s)
        print("all characters: {}".format(s_len))
        m = {}
        for ch in s:
            if ch not in m:
                m[ch] = 0
            m[ch] += 1
        for ch in ["a", "b", "c", "d"]:
            if ch not in m:
                m[ch] = 0
            print("{}: {} => {}%".format(ch, m[ch], m[ch] / s_len * 100))