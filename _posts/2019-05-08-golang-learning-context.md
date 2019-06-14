---
layout: post
title:  "golang learning: Context"
excerpt: "Just about context package in golang."
categories: [golang]
comments: true
---
>Context在golang中出现的频率非常高，因为它实现了golang中两个非常常见的功能。Context的作用主要有两个：在不同的goroutine中传递channel，在不同上下文中传递变量。
针对第二个功能：在上下文中传递变量，我们以Context.Value表示，进行简单介绍。Context.Value可以理解为一个全局变量的容器，只要传递了Context，在所有上下文环境都能使用其中的变量。显而易见，全局变量是具有争议性的，在易于使用的同时，容易被滥用而增加维护成本。在Context.Value的使用范围上，则是见仁见智。个人观点，在上层方法间传递参数，该用还是得用,底层方法则尽量少用。过多依赖Context.Value容易使接口的定义失准，相反，使用明确参数名和结构体会利于接口的定义。
Context的第一个功能，主要用于并发进行的控制。这部分涉及进程间通信的相关技术，传统的做法可以使用信号量，共享变量等技术实现进程间通信。Golang的话，推荐使用channel来解决进程间通信问题。不得不提Golang的哲学之一：Do not communicate by sharing memory; instead, share memory by communicating。通过进程间channel通信代替共享内存。
在没有Context的情况下，我们使用channel控制进程通信的场景一般如下：


### Reference
[How to correctly use context.Context in Go 1.7](https://medium.com/@cep21/how-to-correctly-use-context-context-in-go-1-7-8f2c0fafdf39)
