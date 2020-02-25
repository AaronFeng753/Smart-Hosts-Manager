# Smart-Hosts-Manager
#### 智能管理Hosts文件, 支持IP地址选优

# 简介
Smart-Hosts-Manager主要用于帮助用户在配置Hosts文件时挑选出每个网址最快的IP地址.
用户可以向软件内添加并存储网址和其对应的多个IP, Smart-Hosts-Manager 可以批量对IP执行ping操作并挑选出每个网址对应的延时最低的IP, 最后生成一段包括了每个网址和其对应的最佳IP的Hosts文本.用户只需要将该文本复制到hosts文件内并保存应用即可.

# 使用说明
#### 1.添加网址和IP(以Github为例)

#### 首先添加网址:

#### 然后获取网址的IP:

#### 添加IP:

#### 最后不要忘了保存列表
#### 2.开始测试

#### 3.测试完成后, 将生成的`hosts 文本`复制到`hosts文件`内保存, 最后打开CMD命令行执行`ipconfig /flushdns`刷新dns解析缓存即可.

# 捐赠
![donate](/Donate_QRCode.jpg)
