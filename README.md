# A project base on RZ/G2L
---

##  1.项目整体简介

### 1.1 项目模块
``` 
├── Camera                      相机模块
├── Codec                       编码压缩模块
├── Control                     控制模块
├── Detection                   识别模块
├── QT-UI                       qt模块(即本目录下其他文件组成)
└── Transporter                 推流模块
```

### 1.2 各模块基本文件目录
```
.
├── demo
│   ├── CMakeLists.txt
│   └── Demo.cpp
├── include
│   └── header.hpp
├── README.md
└── src
    └── source.cpp
```

---

## 2.如何构建项目

### 2.1 添加依赖
```
 openCV >=4.40
 QT     >=5.1
 ....(TODO)
```

### 2.2 构建项目

#### 2.2.1 使用qtcreator辅助构建
```
 只需在qtcreator中像正常项目打开构建即可
```

#### 2.2.2 使用qmake构建(推荐)
```
$ cd you/path/to/project
$ qmake -makefile
// change to you Compiler 
$ make -j4
```
#### 2.2.3 使用cmake构建
```
TO DO 
```

---

