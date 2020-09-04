---
layout: post
title: redis集群原理
categories: [redis]
tags: [redis]
description: redis cluster
---

简单看下redis集群的通信数据结构：
typedef struct clusterLink {
	mstime_t ctime; //连接创建时间
	int fd;         //TCP socket 连接文件描述符
    
}
