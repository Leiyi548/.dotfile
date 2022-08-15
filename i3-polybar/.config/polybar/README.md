# polybar

## install

```sh
sudo pacman -S polybar
```

## dependence

```sh
sudo pacman -S xorg-xbacklight nmcli
```

### wifi 模块的设置

使用 `nmcli` 来查看连接 wifi 的接口然后修改接口

例如

```sh
ines 1-18...skipping...
wlp0s20f3: connected to 3202
        "Intel Cannon Point-LP CNVi"
        wifi (iwlwifi), A8:6D:AA:4F:1E:33, hw, mtu 1500
        ip4 default
        inet4 192.168.0.7/24
        route4 192.168.0.0/24 metric 600
        route4 default via 192.168.0.1 metric 600
        inet6 fe80::6832:4340:b753:e112/64
        route6 fe80::/64 metric 1024

p2p-dev-wlp0s20f3: disconnected
        "p2p-dev-wlp0s20f3"
        wifi-p2p, hw

lo: unmanaged
        "lo"
        loopback (unknown), 00:00:00:00:00:00, sw, mtu 65536

DNS configuration:
        servers: 192.168.1.1 192.168.0.1
        interface: wlp0s20f3

Use "nmcli device show" to get complete information about known devices and
"nmcli connection show" to get an overview on active connection profiles.
```

wlp0s20f3: connected to 3202
所以接口是 wlp0s20f3

### 亮度模块接口

使用 backlight 模块可以展示
