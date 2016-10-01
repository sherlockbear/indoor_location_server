def extract(req):
    lis = []
    coord = []
    sp = req.split('+CWLAP:')
    coord.append(int(sp[0].split(',')[0][-2:]))
    coord.append(int(sp[0].split(',')[1][0:2]))
    for i in sp[1:]:
        c = i.split(',')
        lis.append(c[3][1:-1])
        lis.append(int(c[2]))
    return coord,lis
