import pymysql
from extract_fingerprint import extract

my_host='localhost'
my_port=3306
my_user='root'
my_passwd='callmesherlock.b'
my_charset='UTF8'

def storageOfFingerprint(coordinate,req):     #插入数据函数,coordinate为形如[x,y,z]的列表，req为字符串
    data=[0]+coordinate+req
    data=tuple(data)
    conn = pymysql.connect(host=my_host, port=my_port, user=my_user, passwd=my_passwd, charset=my_charset)
    cur = conn.cursor()  # 获取一个游标对象
    cur.execute("USE test1")  # 使用数据库
    cur.execute("INSERT INTO list1 VALUES %s" %(str(data)))  # 插入数据
    cur.close()  # 关闭游标
    conn.commit()  # 向数据库中提交任何未解决的事务，对不支持事务的数据库不进行任何操作
    conn.close()  # 关闭到数据库的连接，释放数据库资源

def database_setup():                       #创建数据库，只需运行一次
    conn= pymysql.connect(host=my_host, port=my_port, user=my_user, passwd=my_passwd, charset=my_charset)
    cur = conn.cursor()  # 获取一个游标对象
    cur.execute("CREATE DATABASE test1")          #执行对应的SQL语句,创建数据库
    cur.execute("USE test1")   #使用数据库
    cur.execute("CREATE TABLE list1 (id INT primary key not null auto_increment,x float,y float, z float,wlan1 char(18),strength1 float,wlan2"
                " char(18),strength2 float,wlan3 char(18),strength3 float,wlan4 char(18),strength4 float)")#创建表
    cur.close()                                    #关闭游标
    conn.commit()                                  #向数据库中提交任何未解决的事务，对不支持事务的数据库不进行任何操作
    conn.close()                                   #关闭到数据库的连接，释放数据库资源

def data_view():                            #查看运行结果,显示数据库中所用数据
    conn = pymysql.connect(host=my_host, port=my_port, user=my_user, passwd=my_passwd, charset=my_charset)
    cur = conn.cursor()  # 获取一个游标对象
    cur.execute("USE test1")   #使用数据库
    cur.execute("SELECT * FROM list1")
    data=cur.fetchall()
    cur.close()                                    #关闭游标
    conn.commit()                                  #向数据库中提交任何未解决的事务，对不支持事务的数据库不进行任何操作
    conn.close()                                   #关闭到数据库的连接，释放数据库资源
    for row in data:
        print('%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s' %row)
