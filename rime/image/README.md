# fcitx5 的自定义主题

非常漂亮

## 使用

`vim ~/.config/fcitx5/conf/classicui.conf`

将下面的参数复制进去（记得修改字体）：

```conf
# 垂直候选列表
Vertical Candidate List=False

# 按屏幕 DPI 使用
PerScreenDPI=True

# Font (设置成你喜欢的字体，不修改字体的话，将使用系统当前默认字体)
Font="Smartisan Compact CNS 13"

# 主题(这里要改成你想要使用的主题名，主题名就在下面)
# 与图片名字相同
Theme=spring
```

保存后，重启输入法皮肤即可生效。
