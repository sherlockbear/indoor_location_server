def extract(req):
    dic = {}
    lis = []
    coord = []
    sp = req.split('+CWLAP:')
    coord.append(int(sp[0].split(',')[0][-2:]))
    coord.append(int(sp[0].split(',')[1][0:2]))
    for i in sp[1:]:
        c = i.split(',')
        dic[c[3][1:-1]]=int(c[2])
    for each_items in sorted(dic.items(),key=lambda d:d[1],reverse = True ):
        lis.extend(list(each_items))
    return coord,lis
