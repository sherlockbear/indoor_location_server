import pymysql
#try:

conn= pymysql.connect(host='localhost', port=3306, user='root', passwd='123456',charset='UTF8')
#conn=pymysql.connect(host='localhost',user='root',passwd='',db='bookdb')
cur=conn.cursor()                              #获取一个游标对象
cur.execute("CREATE DATABASE position")          #执行对应的SQL语句,创建数据库
cur.execute("USE position")   #使用数据库
cur.execute("CREATE TABLE position1 (id INT primary key not null auto_increment,x float,y float, z float,wlan1 char(10),strength1 float,wlan2"
            " char(10),strength2 float,wlan3 char(10),strength3 float,wlan4 char(10),strength4 float)")#创建表
'''
cur.execute("INSERT INTO position1 VALUES(1,10,20,30,'wlan1',50,'wlan4',100,'wlan10',2,'wlan11',24),"
            "(2,60,5,3,'wlan2',50,'wlan5',30,'wlan7',20,'wlan9',34),"
            "(3,15,20,3,'wlan3',60,'wlan5',35,'wlan6',24,'wlan10',16),"
            "(4,7,9,32,'wlan1',89,'wlan4',17,'wlan7',8,'wlan8',36)")#插入数据
            '''
fingerprint1=(0,10,20,30,'wlan1',50,'wlan4',100,'wlan10',2,'wlan11',24)
fingerprint2=(0,60,5,3,'wlan2',50,'wlan5',30,'wlan7',20,'wlan9',34)
fingerprint3=(0,15,20,3,'wlan3',60,'wlan5',35,'wlan6',24,'wlan10',16)
fingerprint4=(0,7,9,32,'wlan1',89,'wlan4',17,'wlan7',8,'wlan8',36)
'''
def tupleToStr(a):
    string=str(a[0])+","+str(a[1])+","+str(a[2])+","+str(a[3])+","+"'"+a[4]+"'"+","+str(a[5])+","+"'"+a[6]+"'"+","+str(a[7])+","+"'"+a[8]+"'"+","+ str(a[9]) +","+"'"+a[10]+"'"+","+str(a[11])
    return string
print("INSERT INTO position1 VALUES (%s),(%s)"%(str(a),str(b)))
a=tupleToStr(a)
b=tupleToStr(b)
'''
newFingerprint=('wlan1',47,'wlan4',108,'wlan10',2,'wlan11',24)
cur.execute("INSERT INTO position1 VALUES %s,%s,%s,%s"%(str(fingerprint1),str(fingerprint2),str(fingerprint3),str(fingerprint4)))#插入四个数据
#cur.execute("SELECT * FROM position1")
cur.execute("select * FROM position1 order by "
            "if(wlan1='%s',strength1,0)+if(wlan2='%s',strength2,0)+if(wlan3='%s',strength3,0)+if(wlan4='%s',strength4,0)+"
            "if(wlan1='%s',strength1,0)+if(wlan2='%s',strength2,0)+if(wlan3='%s',strength3,0)+if(wlan4='%s',strength4,0)+"
            "if(wlan1='%s',strength1,0)+if(wlan2='%s',strength2,0)+if(wlan3='%s',strength3,0)+if(wlan4='%s',strength4,0)+"
            "if(wlan1='%s',strength1,0)+if(wlan2='%s',strength2,0)+if(wlan3='%s',strength3,0)+if(wlan4='%s',strength4,0) "
            "desc limit 3"%(newFingerprint[0],newFingerprint[0],newFingerprint[0],newFingerprint[0],newFingerprint[2],
                newFingerprint[2],newFingerprint[2],newFingerprint[2],newFingerprint[4],newFingerprint[4],
                newFingerprint[4],newFingerprint[4],newFingerprint[6],newFingerprint[6],newFingerprint[6],
                newFingerprint[6]))#查询数据库中与输入信号强度差别最小的三个数据
data=cur.fetchall()

for row in data:
    print('%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s' %row)



cur.close()                                    #关闭游标
conn.commit()                                  #向数据库中提交任何未解决的事务，对不支持事务的数据库不进行任何操作
conn.close()                                   #关闭到数据库的连接，释放数据库资源
#except Exception :print("发生异常")