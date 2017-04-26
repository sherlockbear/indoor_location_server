def extract(req):
    dic = {}
    lis=[]
    for i in req.split('+CWLAP:')[1:]:
        c = i.split(',')
        dic[c[3][1:-1]]=int(c[2])
    for each_items in sorted(dic.items(),key=lambda d:d[1],reverse = True ):
        lis.extend(list(each_items))
    return lis

str1=''
a=[]
f=open("wifi.txt","r")
for each_line in f.readlines():
    f1=open('wifi5.txt','a')
    if each_line[0]=='$':
        print(extract(str1))
        f1.write(str(extract(str1))+'\n')
        a.append(int(each_line.split(',')[0][-1]))
        a.append(int(each_line.split(',')[1][0:2]))
        print(a)
        f1.write(str(a)+'\n')
        str1=''
        a=[]
    else:
        str1 = str1 + each_line
    f1.close
f1=open('wifi5.txt','a')
print(extract(str1))
f1.write(str(extract(str1))+'\n')
f1.close
f.close