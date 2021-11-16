#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>

using namespace muduo;
using namespace muduo::net;

//服务聊天器主类
class ChatServer
{
public:
    //初始化聊天服务器对象
    ChatServer(EventLoop* loop,
            const InetAddress& listenAddr,
            const string& nameArg);
    //启动服务
    void start();

private:
    //上报链接相关信息的回调函数
    void onConnect(const TcpConnectionPtr&);
    //上报读写事件相关信息的回调函数
    void onMessage(const TcpConnectionPtr&,
                  Buffer *,
                  Timestamp);

    TcpServer _server; //服务器类对象
    EventLoop *_loop;  //指向事件循环对象的指针
};

#endif