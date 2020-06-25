# python虚拟机

## 使用方式

```shell
mkdir build
cd build
cmake ..
make all
./pyvm test.pyc
```

## 生成pyc
```shell
python -m compileall test.py
```

## 查看pyc（dis）
```shell
python tools/show_file.py test.pyc
```