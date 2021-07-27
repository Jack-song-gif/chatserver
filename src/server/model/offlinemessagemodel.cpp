#include "offlinemessagemodel.hpp"
#include "db.h"

//存储离线消息
void OfflineMsgModel::insert(int userid, string msg)
{

    //组装sql
    char sql[1024] = {0};
    sprintf(sql, "insert into offlinemessage values(%d,'%s')", userid, msg.c_str());
    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}
//删除离线消息
void OfflineMsgModel::remove(int userid)
{
    char sql[1024] = {0};
    sprintf(sql, "delete from offlinemessage where userid=%d", userid);
    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}
//查询离线消息
vector<string> OfflineMsgModel::query(int userid)
{

    //组装sql
    char sql[1024] = {0};
    sprintf(sql, "select message from offlinemessage where userid=%d", userid);
    vector<string> vec;
    MySQL mysql;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql); //返回结果集
        if (res != nullptr)
        {
            //把userid用户所有的离线消息放到vec中返回
            MYSQL_ROW row; //每次读取一行的数据，放到vec中
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                vec.push_back(row[0]); //因为查询的只有message一个字段
            }
            mysql_free_result(res);
        }
    }
    return vec;
}