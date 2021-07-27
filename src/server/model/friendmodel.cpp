#include "friendmodel.hpp"
#include "db.h"

//添加好友关系
void FriendModel::insert(int userid, int friendid)
{
    //组装sql
    char sql[1024] = {0};
    sprintf(sql, "insert into friend values(%d,%d)",userid,friendid);

    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}

//返回用户好友列表
vector<User> FriendModel::query(int userid)
{
      //组装sql
    char sql[1024] = {0};
    sprintf(sql, "select a.id,a.name,a.state from user a inner join friend  b on b.friendid=a.id where userid=%d", userid);
    vector<User> vec;
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
                User user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setState(row[2]);
                vec.push_back(user);
            }
            mysql_free_result(res);
        }
    }
    return vec;
}