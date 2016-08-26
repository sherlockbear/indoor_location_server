def extract(req):
    lis = []
    for i in req.split('+CWLAP:')[1:]:
        c = i.split(',')
        lis.append(c[3][1:-1])
        lis.append(int(c[2]))
    return lis
