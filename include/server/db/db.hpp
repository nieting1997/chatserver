#ifndef DB_H
#define DB_H

#include <string>
#include <mysql/mysql.h>
using namespace std;

//数据库操作类
class MySQL
{
public:
    // 初始化
    MySQL();
    // 释放
    ~MySQL();
    // 连接
    bool connect();
    // 更新数据
    bool update(string sql);
    // 查询数据
    MYSQL_RES* query(string sql);
    // 获取连接
    MYSQL* getConnection();
private:
    MYSQL *_conn;
};


#endif