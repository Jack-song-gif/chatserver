#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
using namespace muduo;
using namespace muduo::net;

//聊天服务器主类
class ChatServer
{
public:
    //初始化聊天服务器对象  
    ChatServer(EventLoop* loop,const InetAddress& listenAddr,const string& nameArg);
    void start();//启动服务
private:
    //上报连接信息相关的回调函数
    void onConnection(const TcpConnectionPtr&);
    //上报读写事件信息相关的回调函数
    void onMessage(const TcpConnectionPtr&,Buffer*,Timestamp );
    TcpServer _server;//组合的muduo库，实现服务器功能的类对象
    EventLoop *_loop;//事件循环的指针，在合适的时候调用它的quit
};

#endif