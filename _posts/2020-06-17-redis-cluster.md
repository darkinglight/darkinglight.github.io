---
layout: post
title: redis��Ⱥԭ��
categories: [redis]
tags: [redis]
description: redis cluster
---

�򵥿���redis��Ⱥ��ͨ�����ݽṹ��
typedef struct clusterLink {
	mstime_t ctime; //���Ӵ���ʱ��
	int fd;         //TCP socket �����ļ�������
    
}
