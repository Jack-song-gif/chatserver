#ifndef PUBLIC_H
#define PUBLIC_H

/*server与client公共文件*/

enum EnMsgType
{
    LOGIN_MSG = 1,    //登录
    LOGIN_MSG_ACK,    //登录响应消息
    LOGINOUT_MSG,     //注销消息
    REG_MSG,          //注册
    REG_MSG_ACK,      //注册响应消息
    ONE_CHAT_MSG,     //聊天消息
    ADD_FRIEND_MSG,   //添加好友消息
    CREATE_GROUP_MSG, //创建群组消息
    ADD_GROUP_MSG,    //添加群组消息
    GROUP_CHAT_MSG,   //群聊天消息

};

#endif