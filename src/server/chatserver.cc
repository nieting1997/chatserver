#include "chatserver.hpp"
#include "chatservice.hpp"
#include "json.hpp"

#include <functional>
#include <string>

using namespace std;
using namespace placeholders;
using json = nlohmann::json;

ChatServer::ChatServer(EventLoop* loop,
            const InetAddress& listenAddr,
            const string& nameArg)
            :_server(loop, listenAddr, nameArg),
            _loop(loop)
{
    // 注册链接回调
    _server.setConnectionCallback(std::bind(&ChatServer::onConnect, this, _1));
    // 注册消息回调
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));
    // 线程数量
    _server.setThreadNum(4);
}

void ChatServer::start()
{
    _server.start();
}

void ChatServer::onConnect(const TcpConnectionPtr &conn)
{
    // 客户端用户断开连接
    if(!conn->connected())
    {
        ChatService::instance()->clientCloseException(conn);
        conn->shutdown();
    }

}

void ChatServer::onMessage(const TcpConnectionPtr& conn,
                  Buffer *buffer,
                  Timestamp time)
{
    string buf = buffer->retrieveAllAsString();
    json js = json::parse(buf); //反序列化
    // 通过js["msgid"]获取 -> 业务handler -> conn,js,time
    // 完全解耦网络模块代码和业务模块代码
    auto msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>());
    // 回调消息绑定好的事件处理器，执行相应的业务处理
    msgHandler(conn, js, time);
}