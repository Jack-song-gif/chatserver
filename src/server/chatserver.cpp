#include "chatserver.hpp"
#include "chatservice.hpp"
#include "json.hpp"
#include <functional>
#include <iostream>
#include  <string>
using namespace std;
using namespace placeholders;
using json=nlohmann::json;

ChatServer::ChatServer(EventLoop *loop,
                       const InetAddress &listenAddr,
                       const string &nameArg)
    : _server(loop, listenAddr, nameArg), _loop(loop)
{
    //注册连接回调
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));
    
    //注册消息回调函数
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));
    //设置线程数量
    _server.setThreadNum(4);
}

void ChatServer::start() //启动服务
{
    _server.start();
}
//上报连接信息相关的回调函数
void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
    //客户端断开连接
    if(!conn->connected())
    {
        ChatService::instance()->clientCloseException(conn);
        conn->shutdown();
    }
}
//上报读写事件信息相关的回调函数
void ChatServer::onMessage(const TcpConnectionPtr &conn, Buffer *buffer,Timestamp time)
{
    string buf=buffer->retrieveAllAsString();//从缓冲区中读取字符串
    json js=json::parse(buf);//数据的反序列化，相当于解码
    //达到的目的完全解耦网络模块与业务模块，两种方法：面向抽象类（接口）编程，回调操作
    //通过js["msgid"],绑定一个回调操作，获取业务handler=>conn,js,time
    auto msgHandler=ChatService::instance()->getHandler(js["msgid"].get<int>());//注意括号
    //回调消息绑定好的事件处理器，来执行业务处理
    msgHandler(conn,js,time);
}
