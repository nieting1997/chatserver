# chatserver
## 功能
* 用户注册
* 用户登录
* 添加好友，好友聊天
* 添加群组，群组聊天
* 离线消息存储
* nginx配置集群聊天系统
* redis中间件支持跨服务器通信
## 实现
* User,Friend,AllGroup,GroupUser,OfflineMessage等mysql表保存数据
* nginx一致性hash决定用户放置在哪个服务器上
* redis 发布-订阅模式 用来沟通不同服务器上的用户
