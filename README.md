# IPC Learning Project

本项目用于学习 Linux 消息队列。

情景：通过 ./test id 运行的进程 ，连接到一个消息队列上互发消息。其中一个退出时，其它的也会退出。

## 如何实现一个退出其它的也退出

约定：进程退出时会往队列里发送 type=1 的退出信息。

每个进程都有一个循环的线程，它会不停读取队列里的 type=1 信息，读到时向进程发出退出信号。

## 依赖

需要安装 libreadline-dev（Ubuntu）

## 使用

生成可执行文件 test。

```bash
make
```

拆分终端运行多个 test 进程，即可看效果。程序设置了很粗暴的交互功能供使用。
