# [基础使用](https://blog.csdn.net/qq_41530816/article/details/83241760)

- 在需要管理的文件夹下

```shell
$ git init
```

就可以管理该文件夹了。

- 为了更好地使用 git, 同时也记录每一个施加修改的人. 这样人和修改能够对应上. 所以我们在 git 中添加用户名 `user.name` 和 用户 email `user.email`:

```shell
$ git config --global user.name "Whx" 
$ git config --global user.email "Whx@email.com"
```

  

- 通常执行 `$ ls` 就能看到文件夹中的所有文件, 不过 git 创建的管理库文件 `.git` 是被隐藏起来的. 所以我们要执行这一句才能看到被隐藏的文件:

```shell
$ ls -a
```

- 可通过下面命令**创建文件**

```shell
# torch 文件名.后缀    
# 例如
$ torch 1.py
```

- 可以通过<font color ="green">`git status`</font> 来查看版本状态

- 现在 `1.py` 并没有被放入版本库中 (unstaged), 所以我们要使用 `add` 把它添加进版本库 (staged):

```shell
$ git add 1.py (指定文件)
$ git add . （该目录下全部文件）
```

- 提交

```shell
$ git commit -m "注释，可写上本次更改的信息。爱写啥写啥"
```

下面命令配合使用：
```shell
$ git add .
$ git commit -m " " 
```



> - 与Github远程管理

```shell
$ git remote add origin 远程仓库的URL
$ git remote add origin https://github.com/Whx97/ .git 
```

 GitHub 上建立一个仓库，该仓库的URL 只要在仓库网址后面加上`.git` 即可；例如：https://github.com/Whx97/test.git

- 将本地仓库的内容提交到远程仓库

```shell
$ git push origin master
```

# 进阶使用

- 通过下面命令可查看每次提交的历史记录

```shell
$ git log
```

- 如果想要查看这次还没 `add` (unstaged) 的修改部分 和上个已经 `commit` 的文件有何不同, 我们将使用 

```shell
$ git diff
```

  如果已经`add`了这次修改，文件变成了“可提交状态”（staged），可以使用以下命令进行查看

```shell
$ git add .   # add 全部修改文件
$ git diff --cached
```

## 修改已 commit 的版本

有时候我们总会忘了什么, 比如已经提交了 `commit` 却发现在这个 `commit` 中忘了附上另一个文件. 接下来我们模拟这种情况. 比如我创建了`1.py`这个文件并进行了提交，此时我发现我还有一个文件`2.py` 是需要和`1.py`一起上传的。那么我可以使用 `--amend` 将这次改变合并到之前的改变中.

```shell
$ git add 2.py
$ git commit --amend --no-edit   # "--no-edit": 不编辑, 直接合并到上一个 commit
$ git log --oneline    # "--oneline": 每个 commit 内容显示在一行
```

## reset 回到 add 之前

有时我们添加 `add` 了修改, 但是又后悔, 并想补充一些内容再 `add`. 这时, 我们有一种方式可以回到 `add` 之前. 比如在 `1.py` 文件中添加这一行:

```shell
d = 3
```

然后 `add` 去 `staged` 再返回到 `add` 之前:

```shell
$ git add 1.py
$ git status -s # "-s": status 的缩写模式
# 输出
M  1.py     # staged
-----------------------
$ git reset 1.py
# 输出
Unstaged changes after reset:
M   1.py
-----------------------
$ git status -s
# 输出
 M 1.py     # unstaged
```

## reset 回到 commit 之前

每个 `commit` 都有自己的 `id` 数字号, `HEAD` 是一个指针, 指引当前的状态是在哪个 `commit`. 最近的一次 `commit` 在最右边, 我们如果要回到过去, 就是让 `HEAD` 回到过去并 `reset` 此时的 `HEAD` 到过去的位置.

```shell
# 不管我们之前有没有做了一些 add 工作, 这一步让我们回到 上一次的 commit
$ git reset --hard HEAD    
# 输出
HEAD is now at 904e1ba change 2
------------------------------------------------------------
# 看看所有的log
$ git log --oneline
# 输出
904e1ba change 2
c6762a1 change 1
13be9a7 create 1.py
# 这里的 904e1ba 就是指针
------------------------------------------------------------
# 回到 c6762a1 change 1
# 方式1: "HEAD^"  一个^就是向前返回一次
$ git reset --hard HEAD^  

# 方式2: "HEAD~n"  
$ git reset --hard HEAD~1  

# 方式3: "commit id"
$ git reset --hard c6762a1
------------------------------------------------------------
# 看看现在的 log
$ git log --oneline
# 输出
c6762a1 change 1
13be9a7 create 1.py
```

怎么 `change 2` 消失了!!! 还有办法挽救消失的 `change 2` 吗? 我们可以查看 `$ git reflog` 里面最近做的所有 `HEAD` 的改动, 并选择想要挽救的 `commit id`:

```shell
$ git reflog
# 输出
c6762a1 HEAD@{0}: reset: moving to c6762a1
904e1ba HEAD@{1}: commit (amend): change 2
0107760 HEAD@{2}: commit: change 2
c6762a1 HEAD@{3}: commit: change 1
13be9a7 HEAD@{4}: commit (initial): create 1.py
```

重复 `reset` 步骤就能回到 `commit (amend): change 2` (id=904e1ba)这一步了:

```shell
$ git reset --hard 904e1ba
$ git log --oneline
# 输出
904e1ba change 2
c6762a1 change 1
13be9a7 create 1.py
```

我们又再次奇迹般的回到了 `change 2`.