**进入 tty 模式，`ctrl`+`alt`+`f12`**

## 设置镜像

`sudo vim /etc/pacman.conf`

开机 archlinuxcn

- manjaro:

```conf
[archlinuxcn]
# The Chinese Arch Linux communities packages.
#SigLevel = Optional TrustedOnly
SigLevel = Optional TrustAll
#清华大学
Server = https://mirrors.tuna.tsinghua.edu.cn/archlinuxcn/$arch
```

- mirrorlist

```txt
## Country : China
# 清华大学
Server = https://mirrors.tuna.tsinghua.edu.cn/archlinux/$repo/os/$arch
## 163
Server = http://mirrors.163.com/archlinux/$repo/os/$arch
## aliyun
Server = http://mirrors.aliyun.com/archlinux/$repo/os/$arch
# 上海交通大学
Server = https://mirrors.sjtug.sjtu.edu.cn/manjaro/stable/$repo/$arch
```

## 1. 配置 git

### 1.1. 配置 git 用户名，邮箱

```sh
git config --global user.name "username"
git config --global user.email "email.@qq.com"
```

配置完查看是否配置成功 `git config --global --list`
如果没有错误，我们就可以进行下一步了。

### 1.2. 安装 openssh

```sh
sudo pacman -S openssh
```

### 1.3. 生成 ssh 密钥

1.查看是否已经有了 ssh 密钥：cd ~/.ssh
**如果没有密钥则不会有此文件夹，有则备份删除** 2.生存密钥：

```sh
 ssh-keygen -t rsa -C "Your SSH key comment"
```

后面一直回车

然后将 `~/.ssh/id_rsa.pub`内容复制到剪贴版，进入 github 创造一个新的 ssh，将上面复制的内容粘贴进去然后保存。

### 1.3. 验证安装

选择一个自己的仓库，选择 ssh 克隆，然后输入 yes，如果成功克隆，那么恭喜你已经成功配置好 ssh 了。

## 2. 配置 ohmyzsh

zsh 是一个非常好用的 shell，相比于原生的 zsh 更加强大。

但是，自己配置 zsh 是一个非常麻烦的事情，而且不一定能够配置好的，所以，我们就直接用[ohmyzsh](https://github.com/ohmyzsh/ohmyzsh) 。

### 2.1. 安装 zsh

一条命令轻松安装

```sh
sudo pacman -S zsh
```

### 2.2. 设置 zsh 为默认 shell

先查看 zsh 的路径
`which zsh`

`chsh -s /usr/bin/zsh`

**记得重新启动下 archlinux**
查看自己是否设置成功
输出当前`SHELL`：
`echo $SHELL`
查看系统中的`SHELL`：
`cat /etc/shells`

### 2.2. 安装 ohmyzsh

Oh My Zsh is installed by running one of the following commands in your terminal. You can install this via the command-line with either curl, wget or another similar tool.

| Method    | Command                                                                                           |
| :-------- | :------------------------------------------------------------------------------------------------ |
| **curl**  | `sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"` |
| **wget**  | `sh -c "$(wget -O- https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"`   |
| **fetch** | `sh -c "$(fetch -o - https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"` |

国内源加速：

```sh
sh -c "$(curl -fsSL https://gitee.com/lxyoucan/tools/raw/master/common/ohmyzshinstall.sh)"
```

### 2.3. 安装好用的 zsh 插件

- zsh-syntax-highlighting
  ` git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting`

- zsh-autosuggestions
  `git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions`

- zsh-completions
  `git clone https://github.com/zsh-users/zsh-completions ${ZSH_CUSTOM:-${ZSH:-~/.oh-my-zsh}/custom}/plugins/zsh-completions`

- [fzf-tab](https://github.com/Aloxaf/fzf-tab)
  `git clone https://github.com/Aloxaf/fzf-tab ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/fzf-tab`

开启插件，在 `.zshrc` 中找到 plugins

```zsh
plugins=(
	# ohmyzsh builtin plugins
	git
	z
	# user plugins
	zsh-syntax-highlighting
	zsh-autosuggestions
	zsh-completions
	fzf-tab
)
```

### 2.4. 安装好看的主题 powerlevel10k

1. Clone this repository:

[powerlevel10k-github](https://github.com/romkatv/powerlevel10k)

```sh
git clone --depth=1 https://github.com/romkatv/powerlevel10k.git ${ZSH_CUSTOM:-$HOME/.oh-my-zsh/custom}/themes/powerlevel10k
```

中国镜像：

```sh
git clone --depth=1 https://gitee.com/romkatv/powerlevel10k.git ${ZSH_CUSTOM:-$HOME/.oh-my-zsh/custom}/themes/powerlevel10k
```

2. `Set ZSH_THEME="powerlevel10k/powerlevel10k"` in `~/.zshrc`.

3. 配置 powerlevel10k:
   输入命令`p10k configure` 就能根据提示来进行配置 powerlevel10k

修改 powerlevel10k 图标：
`vim .p10k.zsh`

例如：
例如修改图标为 arch：

```sh
  typeset -g POWERLEVEL9K_OS_ICON_CONTENT_EXPANSION=''
```

想要了解更加具体可以看这个链接 <https://github.com/romkatv/powerlevel10k/issues/515>

## 3. 配置 neovim

### 3.1. 安装最新的 neovim 版本

安装需要的依赖：

```sh
sudo pacman -S base-devel cmake unzip ninja tree-sitter curl
```

build 来进行安装最新的 neovim

1.  Install [build prerequisites](https://github.com/neovim/neovim/wiki/Building-Neovim#build-prerequisites) on your system

```sh
sudo pacman -S cmake
```

2.  `git clone https://github.com/neovim/neovim` **如果克隆速度很慢可以换成 ssh 来进行克隆，速度飞起。**
    `sudo pacman -S unzip`
3.  `cd neovim && make CMAKE_BUILD_TYPE=Release`
    - If you want the **stable release**, also run `git checkout stable`.
    - If you want to install to a custom location, set `CMAKE_INSTALL_PREFIX`. See also [Installing Neovim](https://github.com/neovim/neovim/wiki/Installing-Neovim#install-from-source).
    - On BSD, use `gmake` instead of `make`.
    - To build on Windows, see the [Building on Windows](https://github.com/neovim/neovim/wiki/Building-Neovim#building-on-windows) section.
4.  `sudo make install`
    - Default install location is `/usr/local`

如果我们想要查看我 build 的是什么版本：

```sh
./build/bin/nvim --version | grep ^Build
```

如果想要了解更多请看这个[视频](https://www.youtube.com/watch?v=wep2_b_QU7Q)

安装完 neovim 我们安装一些需要的 neovim 插件依赖：

```sh
sudo pacman -S npm
sudo pacman -S fd
# write markdown use this to show file structure
sudo pacman -S tree
# to find text in telescope
sudo pacman -S ripgrep
```

### 3.2. neovim null-ls 依赖

```sh
sudo pacman -S prettier stylua
```

### 3.3. neovim 使用系统剪贴版

我们只需要安装一个东西就可以使用了

```sh
sudo pacman -S xclip
```

然后我们把东西复制到 + 剪贴版就能使用快速复制粘贴。

### 3.4. 安装后启动速度过慢

这个原因是你 neovim build 的版本是 debug 版本 [neovim-issue](https://github.com/neovim/neovim/issues/18670)

解决方案：

1. 删除 build 目录
2. `make CMAKE_BUILD_TYPE=Release`
3. 查看 build 类型：`./build/bin/nvim --version | grep ^Build`
4. 如果是不是 debug 类型，`sudo make install`，就解决了。

## 4. screenkey

平时，如果我需要做视频教程的话，那么我就需要使用一个显示自己按键的软件

### 4.1. 安装

```sh
sudo pacman -S screenkey
# 修改screenkey 位置需要的软件
sudo pacman -S slop
```

### 4.2. 配置

我用的是 i3 可以在左上角看到 screenkey 图标然后能够进行修改。
可以调节：

- 透明度
- 显示区域
- 字体
- 字体大小，颜色

## 5. 配置字体

一个好的字体能够让你生活变得更加舒服。
那么就让我们开始安装一个好的字体吧。

[archwiki-fonts-cn](<https://wiki.archlinux.org/title/Fonts_(简体中文)>)

### 5.1.了解下字体。

- 未单个用户安装
  字体一般都被安装到这个位置 `~/.local/share/fonts`
- 为系统用户安装（所有用户）

### 5.2. 安装字体

通过`pacman`字体安装位置是 `/usr/share/fonts/`

我一般是直接使用`pacman`进行安装

```sh
sudo pacman -S nerd-fonts-complete
yay -S otf-operator-mono-lig
```

当然单独有 nerd-font 是不够，有时候，我们需要一些其他的字体，那么我们要学会如何安装其他字体。

字体来源当然是从对应的字体网站下载获得。

比如我现在已经下载好了`Operator Mono`。

```sh
sudo cp -r OperatorMono /usr/share/fonts/
cd /usr/share/fonts
# 加载字体
fc-cache -fv
```

查看是否安装成功：

`fc-list | grep OperatorMono`

如果出现结果，那么我们就安装成功了。

### 5.3. vscode 使用 Operator mono lig 字体

[下载仓库](https://github.com/SujonHossain1/operator-mono-ligature)
将下载好的字体移动到`~/.local/share/fonts`下面，然后 `fc-cache-fv`就能安装好这个字体

我用的是 archlinux 系统
在 setting.json 加上这么一句：

```json
  "editor.fontFamily": "Operator Mono SSm Lig,微软雅黑",
```

就能使用这个字体了。

### 5.4. kitty 上使用 Operator mono lig 字体

[下载仓库](https://github.com/CarlCaraan/Font-Operator-Mono-Lig)

```sh
git clone https://github.com/CarlCaraan/Font-Operator-Mono-Lig.git
```

将下载好的字体移动到`~/.local/share/fonts`下面，然后 `fc-cache-fv`就能安装好这个字体

我用的是 archlinux 系统
在 kitty.conf 加上这么一句：
因为 Operator Mono Lig 粗体显示效果并不是特别优秀，所以还是用 Operator Mono 来显示粗体

```conf
font_family      Operator Mono Lig
bold_font        Operator Mono
italic_font      Operator Mono Lig
bold_italic_font Operator Mono
```

## 5.5. 安装中文字体

```sh
# 安装 adobe 无衬线字体
sudo pacman -S adobe-source-han-sans-otc-fonts


 #安装 adobe 衬线字体
sudo pacman -S adobe-source-han-serif-otc-fonts


# 安装 noto 中文字体
sudo pacman -S noto-fonts noto-fonts-cjk


# 安装 noto emoji 表情包
sudo pacman -S noto-fonts-emoji
```

## 5.6. ide 使用霞鹜文楷中文字体

我使用这个字体的原因是这个字体比较好看，哈哈。没错，我就是颜值党。

首先我们先去下载这个

```sh
git clone https://github.com/lxgw/LxgwWenKai.git
```

将这个仓库下的 ttf 文件夹里面的字体移动到 `/usr/share/fonts`
然后我们执行 `fc-cache-fv`，这个时候我们就安装成功了。

当然，我们要使用一个字体的话，我们需要知道这个字体叫什么名字。

使用 `fc-list | grep -i lxgw`
![在这里插入图片描述](https://img-blog.csdnimg.cn/70525eb2ebb04f6fb7e678ce13d70294.png)

这个就是我们喜欢的名字，然后我们就可以在自己喜欢的编辑器设置这个字体。

- vscode
  ![在这里插入图片描述](https://img-blog.csdnimg.cn/4861359f8adc4253917fbb338aa56453.png)

- idea

![在这里插入图片描述](https://img-blog.csdnimg.cn/5f4ce321430f4fe883e410ead63a66df.png)

## 6. Stow 管理 dotfile

### 6.1 安装

```sh
sudo pacman -S stow
```

`stow --help` 获得帮助文档：

```sh
# 我这里就说明最经常使用的几个命令。

# 删除一个stow链接
stow -D

# 重新同步一个stow链接
stow -R
```

### 6.2 使用

我就拿 `alacritty` 来进行举例，我在`$HOME`目录下建立一个 .dotfile 文件夹[**这样 stow 管理的默认位置就是$HOME**]，来进行管理这些 stow 好的文件夹。

`alacrrity`的配置在 `~/.config/alacrrity/` 这个文件夹下面。

我们首先在 dotfile 里面建立一个`alacritty`文件夹，文件夹里面的结构是这个样子的：

```txt
alacritty
└── .config
    └── alacritty
        ├── alacritty.yml
        ├── alacritty.yml.bak
        ├── default-arcolinux.yml
        └── default-github.yml
```

注意：

- 如果原来在`~/.config/alacritty`的文件没有被删除的话，那么就会出现问题。

然后我们回到.dotflie 文件夹，然后`stow alacritty`，然后就能在`~/.config/alacritty/` 生成对应的文件和文件夹。

## 7. 配置 fzf

[archwiki-fzf](https://wiki.archlinux.org/title/Fzf)

### 7.1. 安装

```sh
sudo pacman -S fzf
```

### 7.2. 配置

通过 `pacman` 安装的 `fzf` 是和 github 上面安装是不一样的。

安装好的脚本都在 `/usr/share/fzf/key-bindings.zsh`

在 `.zshrc` 最下面添加这么两句话：

```sh
# fzf configuration
# fzf 判断是否存在，然后引用。
[ -f /usr/share/fzf/key-bindings.zsh ] && source /usr/share/fzf/key-bindings.zsh
# enable completion
[ -f /usr/share/fzf/completion.zsh ] && source /usr/share/fzf/completion.zsh
```

然后这个时候，我们就能够使用 `fzf` 的快捷键：

- `Ctrl+t` list files+folders in current directory (e.g., type `git add` , press `Ctrl+t`, select a few files using `Tab`, finally `Enter`)
- `Ctrl+r` search history of shell commands
- `Alt+c` fuzzy change directory

### 7.3. pacman 结合 fzf

Try this to fuzzy-search through all available packages, with package info shown in a preview window, and then install selected packages:

```sh
pacman -Slq | fzf --multi --preview 'pacman -Si {1}' | xargs -ro sudo pacman -S
```

List all your installed packages, and then remove selected packages:

```sh
pacman -Qq | fzf --multi --preview 'pacman -Qi {1}' | xargs -ro sudo pacman -Rns
```

If you want to add package file list in preview – may be a bit slower updating preview window (make sure you run `pacman -Fy` with root privileges at least once before invocation to sync the [pacman](https://wiki.archlinux.org/title/Pacman 'Pacman') file database):

```sh
pacman -Slq | fzf --multi --preview 'cat <(pacman -Si {1}) <(pacman -Fl {1} | awk "{print \$2}")' | xargs -ro sudo pacman -S
```

## 8. lazygit

[lazygit-github](https://github.com/jesseduffield/lazygit)

### 8.1. 安装

```sh
sudo pacman -S lazygit
```

### 8.2 配置

默认配置为 `~/.config/layzgit/config.yml`

[lazygit-configuration-doc](https://github.com/jesseduffield/lazygit/blob/master/docs/Config.md)

使用 `git-delta` 来进行预览

安装 `git-delta`

```sh
sudo pacman -S git-delta
```

配置

```yml
git:
  paging:
    pager: delta
```

## 9. rofi

[rofi-github](https://github.com/davatorium/rofi) 是 i3wm 一个很好的窗口启动器，默认的 rofi 有点丑。

### 9.1. 安装

```sh
sudo pacman -S rofi
```

### 9.2. 配置

rofi 默认配置文件在 `~/.config/rofi/config.rasi`
生成默认配置：

```sh
mkdir -p ~/.config/rofi
rofi -dump-config > ~/.config/rofi/config.rasi
```

[rofi 配置说明](https://github.com/davatorium/rofi/blob/next/CONFIG.md)

### 9.3. 主题

默认的 `rofi` 主题其实很一般，所以我们就需要换一个好看的主题，毕竟**颜值才是第一生产力。**

#### 9.3.1. 快速更换主题

我使用的是 i3 自带的 dmenu 来进行命令

```sh
rofi-theme-selector
```

然后就可以快乐的选择自己喜欢的主题，他会把主题配置写入到配置文件内。

`pacman`安装的主题配置文件在 `/usr/share/rofi/themes/` 内

我现在使用的是 `gruvbox-common`，简单舒服。

## 10. i3 窗口管理器

[archwiki-i3](https://wiki.archlinux.org/title/I3)

### 10.1. 安装

```sh
sudo pacman -S i3
```

### 10.2. i3 浮动窗口

#### 10.2.1. 获取窗口 WM_CLASS

首先我们需要了解哪些窗口是我们要浮动的。
i3wm 识别一个浮动窗口是识别它的 WM_CLASS

你只需要在同一个 workspace 中打开您的应用和终端，在终端中输入`xprop`这里你的鼠标会变成十字线，点击你的应用程序即可获取到窗口的信息。

![](https://img-blog.csdnimg.cn/be7b6111e68a4e61b8905965292b0aae.png)

更方便的方法查询 WM_CLASS

```sh
xprop | grep WM_CLASS
```

WM_CLASS 的第一部分是实例（本例中为“jetbrains-idea”），第二部分是类（本例中为“jetbrains-idea”）。
**记得选第二个名字**

i3wm 启动窗口指定浮动窗口的大小和位置

示例：

```sh
for_window [class="窗口"] floating enable resize set 640 480,move right 330px,move down 70px
```

## 11. polybar

默认的 i3-status 有点简陋，这个是用来替代的。
[polybar-github](https://github.com/polybar/polybar)

### 11.1. 安装

```sh
sudo pacman -S polybar
```

### 11.2. 配置

polybar 的默认配置在 `/etc/polybar/config.ini`，也可以自定义在 `~/.config/ploybar/config.ini`

复制默认配置：

```sh
mkdir ~/.config/polybar
cp /etc/polybar/config.ini ~/.config/polybar/config.ini
```

## 12. 音量、亮度调节

[参考文章|csdn](https://blog.csdn.net/olnautunm/article/details/110088697)

### 12.1. 亮度调节

安装依赖：

```sh
yay -S light-git
```

写入 i3 配置文件：

```config
bindsym XF86MonBrightnessUp exec light -A 10 # increase screen brightness
bindsym XF86MonBrightnessDown exec light -U 10 # decrease screen brightness
```

### 12.2. 音量调节

安装

```sh
sudo pacman -S alsa-utils
```

使用 `alsamixer` 来启动
通过方向键或者 jk 来调节音量。
`esc` 退出。

## 13.ranger 文件管理器

### 13.1. 安装

```sh
sudo pacman -S ranger
```

### 13.2. 配置

#### 13.2.1. 使用图标

```sh
git clone https://github.com/alexanderjeurissen/ranger_devicons ~/.config/ranger/plugins/ranger_devicons
echo "default_linemode devicons" >> $HOME/.config/ranger/rc.conf
```

#### 13.2.2. 整合 git

在 `~/.config/ranger/rc.conf`

```sh
set vcs_aware true
```

更多信息请看 [VCS integration](https://github.com/ranger/ranger/wiki/VCS-integration)

### 13.3. 使用 kitty 终端预览图片

安装 pip

```sh
sudo pacman -S python-pip
```

安装 pillow （为了能够使用 ranger 来预览图片）

```sh
pip3 install -i https://mirrors.aliyun.com/pypi/simple pillow
```

修改 rc.conf :

```sh
set preview_images true
set preview_images_method kitty
```

然后，我们就能愉快的使用 ranger 来进行图片预览了。

### 13.3. 参考文章

- [终端中的文件管理器 ranger](https://blog.csdn.net/lxyoucan/article/details/115671189)

## 14. 常用简单软件下载

more information please see <https://arch.icekylin.online/apps/daily.html>

### 14.1. 开发工具

- alacritty

```sh
sudo pacman -S alacritty
```

- kitty

```sh
sudo pacman -S kitty
```

- vscode

```sh
yay -S visual-studio-code-bin
```

- vscode-rofi

```sh
yay -S rofi-code-git
```

- dunst （通知）

```sh
sudo pacman -S dunst
```

- ide

```sh
sudo pacman -S intellij-idea-ultimate-edition
sudo pacman -S intellij-idea-ultimate-edition-jre

sudo pacman -S webstorm
sudo pacman -S webstorm-jre
```

### 14.2. 浏览器

- Chrome

```sh
yay -S google-chrome
```

- Firefox

```sh
sudo pacman -S firefox
```

- Microsoft Edge

```sh
yay -S microsoft-edge-stable-bin
```

### 14.3. 休闲

#### 14.3.1. qq 微信

- qq and wechat

**记得在/etc/pacom.conf 中开启 multib 这个镜像库下载需要里面的依赖**
**要不然会一直安装不成功**

```sh
yay -S deepin-wine-wechat icalingua++
# 垃圾 linux qq 建议使用上面那个
# yay -S deepin-wine-qq
```

##### 14.3.2. wine 放大字体

默认的字体很小，让我很难受，看久了人都要瞎了。
所以，我们需要调字体。

```sh
 /opt/apps/com.qq.weixin.deepin/files/run.sh winecfg
```

![wine](https://img-blog.csdnimg.cn/1b8226414ca445cda609b2404f75f06a.png)

#### 解决出现阴影在微信屏幕上

每次重新启动，都会重新出现。

下载依赖

```sh
sudo pacman -S winctrl xwininfo
```

更多详细信息请看这 <https://zhuanlan.zhihu.com/p/106926984>

##### 14.4. 解决 wechat 中文字体乱码

###### 14.4.1. 下载字体

到[github 下载字体](https://github.com/qiuhuachuan/fonts/blob/main/MSYH.TTC)，点击"下载" ，字体文件默认存储到 Downloads 文件夹内。

###### 14.4.2. 將字体复制到指定的位置

`cp ~/Downloads/MSYH.TTC ~/.deepinwine/Deepin-WeChat/drive_c/windows/Fonts`

##### 14.4.3. 將字体注册到 Wine

`vim ~/.deepinwine/Deepin-WeChat/font.reg`

键入以下内容，然后保存。

```reg
REGEDIT4
[HKEY_LOCAL_MACHINE\Software\Microsoft\Windows NT\CurrentVersion\FontSubstitutes]
"MS Shell Dlg"="msyh"
"MS Shell Dlg 2"="msyh"

[HKEY_LOCAL_MACHINE\Software\Microsoft\Windows NT\CurrentVersion\FontLink\SystemLink]
"Lucida Sans Unicode"="msyh.ttc"
"Microsoft Sans Serif"="msyh.ttc"
"MS Sans Serif"="msyh.ttc"
"Tahoma"="msyh.ttc"
"Tahoma Bold"="msyhbd.ttc"
"msyh"="msyh.ttc"
"Arial"="msyh.ttc"
"Arial Black"="msyh.ttc"
```

#### 14.3.2. telegram

- telegram

```sh
sudo pacman -S telegram-desktop
```

#### 14.3.3. YesPlayMusic（推荐 支持网易云）

- YesPlayMusic（推荐 支持网易云）

```sh
yay -S yesplaymusic
```

##### 14.3.4. 网易云音乐

- 网易云音乐

```sh
yay -S netease-cloud-music
```

### 14.4. 办公

#### 14.4.1 坚果云

```sh
yay -S nutstore
```

#### 14.4.2. 百度网盘

```sh
yay -S baidunetdisk-bin
```

#### 14.4.3. obsidian

```sh
sudo pacman -S obsidian
```

#### 14.4.4. office

```sh
# 安装国内版 office,安装字体
yay -S wps-office-cn ttf-wps-fonts
# 中文语言包（建议安装）
yay -S wps-office-mui-zh-cn
```

#### 14.4.5. 滴答清单

```sh
yay -S dida-bin
```

#### 14.4.6. utools

```sh
yay -S utools
```

#### 14.4.7. SMplayer (视频播放器)

```sh
sudo pacman -S SMplayer
```

#### 14.4.8. (钉钉)

```sh
yay -S dingtalk-bin
yay -S dingtalk-electron
```

#### 14.4.9. 腾讯会议

```sh
yay -S wemeet-bin
```

### pdf 阅读

```sh
yay -S foxitreader
```

### 14.5. 炫技

#### 14.5.1. cmatrix

```sh
sudo pacman -S cmatrix
```

### 14.6. 图片查看器

- ristretto

```sh
sudo pacman -S ristretto
```

### 14.7. colorpicker

[archwiki-colorpicker-aur](https://aur.archlinux.org/packages/colorpicker)

```sh
git clone https://aur.archlinux.org/colorpicker.git
cd colorpicker
makepkg -si
```

然后我们就能愉快的使用 colorpicker 获得颜色了。在终端

如果你想用 gui 的页面，那么你就使用这个`Gcolor2`

### 14.8. 思维导图

- minder

```sh
sudo pacman -S minder
```

### 14.9. 直播平台

- obs-sudio

```sh
sudo pacman -S obs-studio
```

- screenkey

```sh
sudo pacman -S screenkey dbus-python slop
```

## 15. 丝滑动画 picom

如果使用的是 `yay` 里面自带的 `pciom` 是缺少很多特性的。

那么我们用一个 [fork 版本](https://github.com/dccsillag/picom/tree/implement-window-animations)。
[我还使用的是我关注的 b 站 up 主 fork fork 版本](https://github.com/yaocccc/picom/tree/implement-window-animations)

### 15.1 安装

```sh
git clone git@github.com:yaocccc/picom.git
cd picom
git checkout implement-window-animations
```

### 15.2. 安装依赖

```sh
sudo pacman -S meson ninja libev uthash libconfig
```

### 15.3. 安装

```sh
git submodule update --init --recursive
meson --buildtype=release . build
sudo ninja -C build install
```

### 15.2. 参考教程

- [linux 丝滑的动画体验](https://yaocc.cc/2022/06/19/linux丝滑的动画体验——picom/)

## 16. networkmanger

### 16.1. 安装

在 archlinux 中我们需要连接 WiFi 我们需要安装下面这些东西

```sh
pacman -S networkmanager nm-connection-editor  network-manager-applet rp-pppoe
systemctl enable NetworkManager
```

然后我们就拥有了一个 gui 的 wifi 连接器。

## 17. z.lua

### 17.1. 安装

安装 z.lua

```sh
git clone https://github.com/skywind3000/z.lua ~/script/
```

然后在 `~/.zshrc` 里面添加

```zsh
# 默认普通模式
eval "$(lua ~/tmp/z.lua/z.lua  --init zsh)"
# 开启增强模式
eval "$(lua ~/tmp/z.lua/z.lua  --init zsh once enhanced)"
```

### 17.2. 使用

数据文件都放在 `~/.zlua里面`

在不带参数的时候按 `z` 会显示出所有路径和频率。

更多详细信息请看这里：

eval "$(lua ~/tmp/z.lua/z.lua --init zsh once enhanced)"

## 18. pacman 和 yay 常用命令

### 18.1. pacman

- S：安装
- Ss： 从 pacman 搜索安装包
- Syyu：每日更新
- Ql ： 从已经安装好的包进行搜索

### 18.2. yay

- S : 安装
- Sy：从远程镜像获取软件包更新信息
- Syy：强制获取更新信息
- Syyu：更新软件包
- Sc：删除以下载的过时安装包
- Syyw：下载较新的软件包，但不安装
- Ss：从远程仓库中搜索软件包
- R：删除软件
- Rs：删除软件及其依赖文件
- Rns：删除软件和依赖文件及其配置文件
- Qe：显示用户安装的软件包
- Qq：不输出软件的版本信息
- Qn：显示从官方镜像中下载的软件
- Qm：显示从 AUR 中下载的软件
- Qdt：显示孤包
- Qs：显示本地库的包

## 19. 常见问题

### 19.1. Connecting to raw.githubusercontent.com :443... failed: Connection refused.

我们先去这个[网站](https://www.ipaddress.com/)查询 `raw.githubusercontent.com`

然后就把查找到的 host 然后 `sudo vim /etc/hosts`

然后在尾部添加这个数据：

```txt
185.199.108.133 raw.githubusercontent.com
```

类似上面形式，这个问题就解决了。

### 19.2. archlinux 电量不更新

自从升级入了 archlinux 5.19 的内核就发现电池电量不更新

那么我就用了我的 google 大法，终于搜索到我想要的内容了。

在这个文件 `/etc/modprobe.d/asus_ec_sensors.conf`
加人这么一句话：

```conf
blacklist asus_ec_sensors
```

然后重启，我们这个时候就能更新电量了。

## 20. 使用技巧

### 20.1 查找文件并删除

例如，我现在文件中有这么一群文件，如下图所示：

```txt
.
├── 1.aaa.txt
├── 1.bbb.txt
├── 2.aaa.txt
└── 2.bbb.txt
```

然后我们要实现的目标是删除文件名包含`1.`的文件。

那么，我们就写一个 shell 脚本

```sh
# 查找文件放入到一个数组内
file_list=`fd '1.'`
# 循环删除
for file in ${file_list}
do
  rm ${file}
done
```

然后我们执行命令，就能看到删除成功了。

```
.
├── 2.aaa.txt
└── 2.bbb.txt
```

### 20.2. grep 遍历一个文件夹里面的内容

`grep -r "要查找的内容" ./`

![在这里插入图片描述](https://img-blog.csdnimg.cn/9d2e8e881f03431db9b2628c1cb953ce.png)

### 20.3. 删除文件——排除指定文件

#### 20.3.1. 情形

当前状态：

```txt
.
├── 1.txt
├── 2.txt
├── 3.txt
├── 4.txt
└── 5.txt
```

然后我想删除只保留 1.txt。

#### 20.3.2. 使用!()

`rm !(1.txt)`

正常情况下是全部文件被删除了，只留下了 1.txt，但是有时候我们的系统没配置好，可能会报错，例如下面这种：

```txt
-bash: !: event not found
```

上面这种情况是因为我们的系统没有开启通配符功能，我们执行下面的命令开启通配符功能先：

`shopt -s extglob`

查看通配符功能是否开启，on 表示已经开启

`shopt -s`
![在这里插入图片描述](https://img-blog.csdnimg.cn/71d70d90f75e4bf0b448a3d63af950a2.png)

查看删除后的文件

```txt
.
└── 1.txt
```

#### 20.3.3. 使用 grep -v 排除然后删除

**推荐使用这个方法，因为可以直接用 zsh 来进行操作**

`find *.txt | grep -v 1.txt | xargs rm`

#### 20.3.4. 参考文件

[Linux 下使用 rm 删除文件，并排除指定文件](https://cloud.tencent.com/developer/article/2045451)

## 21. advanced fzf

### 21.1. 安装依赖

```sh
sudo pacman -S the_silver_searcher bat
```

[script 来源](https://github.com/DanielFGray/fzf-scripts/blob/master/fv)
[Linux xargs 命令](https://www.runoob.com/linux/linux-comm-xargs.html)

## 22. 配置 npm 镜像

首先我们查看我们的镜像地址

```sh
npm get registry
```

正常来说，我们没有更改镜像地址。
默认是 `https://registry.npmjs.org/`

切换淘宝镜像

```sh
npm config set registry http://registry.npm.taobao.org/
```

设置好我们再查看下：

`npm get registry` 然后我们就能看到 `npm config set registry http://registry.npm.taobao.org/`说明我们设置成功。

## 23. vscode 输入法问题

在 linux 下我们实现的输入法基本上都是 fcitx 其他输入法，我也不了解在 linux。

在`setting.json`

添加这句

```json
  "vim.autoSwitchInputMethod.enable": true,
  "vim.autoSwitchInputMethod.defaultIM": "1", // 1033
  "vim.autoSwitchInputMethod.obtainIMCmd": "/usr/bin/fcitx5-remote",
  "vim.autoSwitchInputMethod.switchIMCmd": "/usr/bin/fcitx5-remote -t {im}",
```

## 24. 改变 manjaro 主题

下载依赖

```sh
sudo pacman -S gnome-themes-extra gnome-icon-theme-extras
```

使用命令 `lxappearance`

改变 qt 主题
使用命令 `qt5ct`
